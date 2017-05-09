#pragma once

#include "Vector2D.h"
#include <vector>

using std::vector;

/**
*
*/
class PathNode{
	public:
		PathNode(int ID, const Vector2D &Position, int Cost = 0, vector<int> Connected = vector<int>(), PathNode *Parent = nullptr, bool bIsPassable = true);
		~PathNode();

		int ID;
		Vector2D Position;
		int Cost;
		vector<int> Connected;
		PathNode *Parent;
		bool bIsPassable;



		inline bool operator==(const PathNode &rhs) const{
			if(this == &rhs){
				return true;
			}

			return ID == rhs.ID;
		}
};