#include "Collisions.h"
#include "Mathf.h"

Cell::Cell()
	:
	mpBoxes(new std::vector<BoxCollider*>)
{
	mpBoxes->reserve(5);
}

Cell::~Cell()
{
	Clear();
	delete mpBoxes;
}
const bool Cell::IsCollide(const Vector2f& point) const
{
	for (BoxCollider*& box : *mpBoxes)
	{
		if (box->IsPointOver(point))
		{
			return true;
		}
	}
	return false;
}
const bool Cell::IsCollide(const BoxCollider& other) const
{
	for (BoxCollider*& box : *mpBoxes)
	{		
		if (box != &other && box->IsOverlap(other))
		{
			other.mOther = box;
			return true;
		}
	}
	other.mOther = NULL;
	return false;
}

#include <iostream>
void Cell::Add(BoxCollider* box)
{
	if (!IsContains(box))
		mpBoxes->push_back(box);
}

void Cell::Remove(const BoxCollider* box)
{
	const size_t& length = mpBoxes->size();
	for (size_t i = 0; i < length; i++)
	{
		if ((*mpBoxes)[i] == box)
		{
			mpBoxes->erase(mpBoxes->begin() + i);
			break;
		}
	}
}

void Cell::Clear()
{
	mpBoxes->clear();
}

const bool Cell::IsContains(const BoxCollider* box) const
{
	const size_t& length = mpBoxes->size();
	for (size_t i = 0; i < length; i++)
	{
		if ((*mpBoxes)[i] == box)
		{
			return true;
		}
	}
	return false;
}


Collisions::~Collisions()
{
}

void Collisions::Clear()
{
	for (size_t i = 0; i < gridLength; i++)
	{
		GetInstance().mGrid[i].Clear();
	}
}

void Collisions::OccupyCell(BoxCollider& box, const BoxCollider& oldBox)
{
	for (size_t i = 0; i < 4; i++)
	{
		const Vector2f& oldPos = oldBox.GetCorner(i);
		GetInstance().GetCell(oldPos).Remove(&box);
	}

	for (size_t i = 0; i < 4; i++)
	{
		const Vector2f& pos = box.GetCorner(i);
		GetInstance().GetCell(pos).Add(&box);
	}
}

bool Collisions::IsCollide(BoxCollider& box)
{
	for (size_t i = 0; i < 4; i++)
	{
		const Vector2f& pos = box.GetCorner(i);
		const Cell& cell = GetInstance().GetCell(pos);
		if (cell.IsCollide(box))
		{
			return true;
		}
	}
	return false;
}

Collisions::Collisions()
{
}

Collisions& Collisions::GetInstance()
{
	static Collisions collision;
	return collision;
}

Cell& Collisions::GetCell(const Vector2f& position)
{
	const Vector2i pos(
		int(roundf(position.x)) / cellWidth  - 1, 
		int(roundf(position.y)) / cellHeight - 1);

	const int index = Mathf::Clamp(0, gridLength - 1, pos.y * cellCol + pos.x);
	return GetInstance().mGrid[index];
}
