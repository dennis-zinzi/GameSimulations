#include "AStar.h"

/**
* Prepares and calls A* algorithm
*/
vector<Vector2D> AStar::GetAStarPath(const Vector2D &StartPos, const Vector2D &EndPos, vector<PathNode*> &NodeMap){
	//Get start node (AI)
	PathNode *start = GetClosestNode(StartPos, NodeMap);
	//Get start node (Player)
	PathNode *end = GetClosestNode(EndPos, NodeMap);

	//Check Nodes actually exist
	if(!start){
		cout << "ERROR: Start node not found" << endl;
		return vector<Vector2D>();
	}
	if(!end){
		cout << "ERROR: End node not found" << endl;
		return vector<Vector2D>();
	}

	if(start == end){
		cout << "ERROR: Start node is end node" << endl;
		vector<Vector2D> arr;
		arr.push_back(start->Position);
		arr.push_back(end->Position);
		return arr;
	}

	//Create an Open and Closed List for the A* search
	vector<PathNode*> OpenList,
		ClosedList;

	//Check Path available
	if(AStarAlgorithm(start, end, NodeMap, OpenList, ClosedList)){
		cout << "PATH IS AVAILABLE!!!" << endl;
		return GeneratePath(start, end, ClosedList);
	}
	else{
		cout << "ERROR MAKING PATH" << endl;
		return vector<Vector2D>();
	}
}



/**
* Actual A* Algorithm
*/
bool AStar::AStarAlgorithm(PathNode *StartNode, PathNode *FinalNode, vector<PathNode*> &NodeList, vector<PathNode*> &OpenList, vector<PathNode*> &ClosedList){
	//Check there are actually nodes to traverse
	if(NodeList.size() == 0){
		cout << "NO NODES TO EXPLORE" << endl;
		return false;
	}

	//Initialization
	float G = CostToMove(StartNode->Position, StartNode->Position),
		H = HeuristicCost(StartNode->Position, FinalNode->Position);

	StartNode->Cost = G + H;
	OpenList.push_back(StartNode);

	//End Initialization

	if(OpenList.size() == 0){
		cout << "NOTHING IN OPEN LIST" << endl;
		return false;
	}

	//Safety number to prevent infinite execution
	int num = 0;

	//While nodes to explore are available create path
	while(OpenList.size() > 0 && num < MAX_ITERATIONS){
		PathNode *Current = GetMinCostNode(OpenList);

		//Check node is real
		if(!Current){
			cout << "NODE NOT FOUND" << endl;
			return false;
		}

		//Remove current node from Open List (already explored)
		auto it = find(OpenList.begin(), OpenList.end(), Current);
		if(it != OpenList.end()){
			auto index = distance(OpenList.begin(), it);
			OpenList.erase(it);
		}
		//OpenList.erase(Current);

		//Check if Node has children, if not find them
		if(Current->Connected.empty()){
			bool isConnected = FindNodeConnections(Current, NodeList);

			//Check node actually has connections, reject it if it doesn't
			if(!isConnected){
				cout << "NO CONNECTIONS TO NODE, ID: " << Current->ID << endl;
				continue;
			}
		}

		//Get G value of Current Node
		const int GCostCurrent = Current->Cost - HeuristicCost(Current->Position, FinalNode->Position);

		//Iterate through all of the connected nodes
		for(int i = 0; i < Current->Connected.size(); i++){
			//Get Child node
			PathNode *Successor = GetMatchingNodeByID(Current->Connected[i], NodeList);
			if(!Successor){
				continue;
			}

			//If the child node is the goal, we have a winner
			if(Successor->ID == FinalNode->ID){
				cout << "WE HAVE A PATH" << endl;
				Successor->Parent = Current;
				ClosedList.push_back(Current);
				return true;
			}

			//Check if node is actually possible to go through
			if(!Successor->bIsPassable){
				//Ignore if it isn't
				continue;
			}

			//Recalculate Cost to reach node (Add G cost of current node)
			const int cost = GCostCurrent + CostToMove(Current->Position, Successor->Position) + HeuristicCost(Successor->Position, FinalNode->Position);

			//If Node already in open list with a cheaper cost, then ignore
			auto itOpen = find(OpenList.begin(), OpenList.end(), Successor);
			if(itOpen != OpenList.end()){
				if(Successor->Cost < cost){
					continue;
				}
			}
			/*if(OpenList.Contains(Successor) && Successor->Cost < cost){
				continue;
			}*/

			//If Node already in closed list with a cheaper cost, then ignore
			auto itClosed = find(ClosedList.begin(), ClosedList.end(), Successor);
			if(itClosed != ClosedList.end()){
				if(Successor->Cost < cost){
					continue;
				}
			}
			/*if(ClosedList.Contains(Successor) && Successor->Cost < cost){
				continue;
			}*/

			//Otherwise update the child's cost, and set it's parent to current node
			Successor->Cost = cost;
			Successor->Parent = Current;

			//If child not in open list, add it
			OpenList.push_back(Successor);
			num++;
		}

		//Add Current node to closed list
		ClosedList.push_back(Current);
		num++;
	}

	//If reached here, no path exists to player
	cout << "NO POSSIBLE PATH, after " << num << " iterations" << endl;
	return false;
}


/**
* Generates the FVector Array of positions to in the path
*/
vector<Vector2D> AStar::GeneratePath(PathNode *StartNode, PathNode *FinalNode, const vector<PathNode*> &ClosedList){
	//Array containing final nodes (vector as can be reversed)
	vector<PathNode*> FinalNodes;

	//Final path to Player
	vector<Vector2D> Path;

	//Start from final node and make your way upwards
	PathNode *R = FinalNode;

	//Safety int to prevent infinite loop
	int num = 0;

	while(R && R->ID != StartNode->ID && num < 1000){
		FinalNodes.push_back(R);
		R = GetMatchingNodeByID(R->Parent->ID, ClosedList);
		num++;
	}

	//Since Nodes have been added in reverse order, need to reverse the array
	reverse(FinalNodes.begin(), FinalNodes.end());


	//Add the positions the AI has to traverse
	for(auto Node : FinalNodes){
		Path.push_back(Node->Position);
	}


	return Path;
}


/**
* Determines Heuristic cost of moving from one position to another, using Manhattan Distance
*/
int AStar::HeuristicCost(const Vector2D &Source, const Vector2D &Destination){
	Vector2D dist = Source - Destination;
	return (int)(abs(dist.getX()) + abs(dist.getY()));
}

/**
* Determines cost of moving from one position to another, using Manhattan Distance
*/
int AStar::CostToMove(const Vector2D &Source, const Vector2D &Destination){
	Vector2D dist = Source - Destination;
	return (int)(abs(dist.getX()) + abs(dist.getY()));
}


/**
* Populates Neighboring nodes list for given Node
*/
bool AStar::FindNodeConnections(PathNode *Node, vector<PathNode*> &List){
	//Empty list currently there
	Node->Connected.clear();

	float NodeX = Node->Position.getX(),
		NodeY = Node->Position.getY();


	for(float x = NodeX - TILE_LENGTH; x < NodeX + TILE_LENGTH + 1; x += TILE_LENGTH){
		for(float y = NodeY - TILE_LENGTH; y < NodeY + TILE_LENGTH + 1; y += TILE_LENGTH){
			//Skip if location is current node's
			if(x == NodeX && y == NodeY){
				continue;
			}

			PathNode* found = GetNodeWithXY(x, y, List);

			if(found){
				Node->Connected.push_back(found->ID);
			}
		}
	}

	//Check if any connections made
	return Node->Connected.empty() ? false : true;
}

/*
*  ----------------------------------------------------------
*	---------------PathNode Helper Functions------------------
*	----------------------------------------------------------
*/
PathNode* AStar::GetMatchingNodeByID(const int ID, const vector<PathNode*> &List){
	for(auto Node : List){
		if(Node->ID == ID){
			return Node;
		}
	}

	return nullptr;
}


PathNode* AStar::GetMinCostNode(const vector<PathNode*> &List){
	PathNode *Min = List.size() > 0 ? List[0] : nullptr;

	for(auto Node : List){
		if(Node->Cost < Min->Cost){
			Min = Node;
		}
	}

	return Min;
}


PathNode* AStar::GetNodeWithXY(const float x, const float y, const vector<PathNode*> &List){
	for(auto Node : List){
		if(Node->Position.getX() == x && Node->Position.getY() == y){
			return Node;
		}
	}

	return nullptr;
}


PathNode* AStar::GetClosestNode(const Vector2D &Pos, const vector<PathNode*> &List){
	PathNode *Closest = List.size() > 0 ? List[0] : nullptr;

	//Set large value as default smallest distance
	float dist = 999999.0f;

	for(auto Node : List){
		if(!Node->bIsPassable){
			continue;
		}

		float DistToNode = abs(Vector2D::distance(Pos, Node->Position));

		if(DistToNode < dist){
			Closest = Node;
			dist = DistToNode;
		}

	}

	return Closest;
}


PathNode* AStar::GetClosestNeighborNode(const Vector2D &CurPos, const Vector2D &GoPos, vector<PathNode*> &List){
	PathNode *Current = GetClosestNode(CurPos, List);
	if(!Current){
		return nullptr;
	}

	if(Current->Connected.empty()){
		if(!FindNodeConnections(Current, List)){
			cout << "NO CONNECTIONS TO NODE, ID: " << Current->ID << endl;
			return nullptr;
		}
	}

	//Set large value as default smallest distance
	float dist = 999999.0f;
	PathNode *winner = nullptr;

	for(int i = 0; i < Current->Connected.size(); i++){
		PathNode *Successor = GetMatchingNodeByID(Current->Connected[i], List);
		if(!Successor){
			continue;
		}
		if(!Successor->bIsPassable){
			continue;
		}

		float nodeDist = abs(Vector2D::distance(Successor->Position, GoPos));
		if(nodeDist < dist){
			dist = nodeDist;
			winner = Successor;
		}
	}

	return winner;
}