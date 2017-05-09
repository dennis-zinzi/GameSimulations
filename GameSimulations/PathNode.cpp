#include "PathNode.h"


PathNode::PathNode(int ID, const Vector2D &Position, TileType terrain, int Cost, vector<int> Connected, PathNode *Parent, bool bIsPassable){
	this->ID = ID;
	this->Position = Position;
	this->Cost = Cost;
	this->Connected = Connected;
	this->Parent = Parent;
	this->bIsPassable = bIsPassable;
	this->terrain = terrain;
}


PathNode::~PathNode(){
}

float PathNode::GetTerrainCost(){
	switch(terrain){
		case BASE:
		case OPEN:
		case COVERED:
		case BRIDGE:
		case CASTLE:
			return 1.0f;
		case FOREST:
			return 1.5f;
		case RIVER:
			return 1.65f;
		case GATE:
			return 1.85f;
		//Used for impulse
		case WALL:
			return 10.0f;
		default:
			return 1.0f;
	}
}
