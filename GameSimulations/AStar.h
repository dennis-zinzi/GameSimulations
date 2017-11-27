/**
* Manages calculating A* search pathfinfing
*/
#pragma once

#include "common.h"

#include "PathNode.h"
#include "Vector2D.h"

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::find;
using std::distance;

#define MAX_ITERATIONS 10000

class AStar{
	public:

		//Get A* Vector list of locations to move through
		static vector<Vector2D> GetAStarPath(const Vector2D &StartPos, const Vector2D &EndPos, vector<PathNode*> &NodeMap);

		//Get A* Vector list of tactical locations to move through
		static vector<Vector2D> GetTacticalAStarPath(const Vector2D &StartPos, const Vector2D &EndPos, vector<PathNode*> &NodeMap);

		//Gets closest node to position
		static PathNode* GetClosestNode(const Vector2D &Pos, const vector<PathNode*> &List);

		//Gets closest wall/gate node to position
		static PathNode* GetClosestTacticalNode(const Vector2D &Pos, const vector<PathNode*> &List);

		//Gets closest neighboring node to position
		static PathNode* GetClosestNeighborNode(const Vector2D &CurPos, const Vector2D &GoPos, vector<PathNode*> &List);

	private:
		
		static bool AStarAlgorithm(PathNode *StartNode, PathNode *FinalNode, vector<PathNode*> &NodeList, vector<PathNode*> &OpenList, vector<PathNode*> &ClosedList);
		static bool AStarTacticalAlgorithm(PathNode *StartNode, PathNode *FinalNode, vector<PathNode*> &NodeList, vector<PathNode*> &OpenList, vector<PathNode*> &ClosedList);
		
		static int HeuristicCost(const Vector2D &Source, const Vector2D &Destination);
		static int CostToMove(const Vector2D &Source, const Vector2D &Destination);

		static vector<Vector2D> GeneratePath(PathNode *StartNode, PathNode *FinalNode, const vector<PathNode*> &ClosedList);

		static PathNode* GetMinCostNode(const vector<PathNode*> &List);
		static PathNode* GetMatchingNodeByID(const int ID, const vector<PathNode*> &List);
		static PathNode* GetNodeWithXY(const float x, const float y, const vector<PathNode*> &List);

		static bool FindNodeConnections(PathNode *Node, vector<PathNode*> &List);
};