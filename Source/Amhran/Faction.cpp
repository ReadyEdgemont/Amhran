// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Faction.h"

UFaction::UFaction()
{
	for(int i = 0; i < NUMFACTIONS; i++)
	{
		for(int ii = 0; ii <= i; ii++)
		{
			map[i][ii] = false;
		}
	}
	/*------------------
	* Add Hostilities Here!!!!
	------------------*/
	addHostility(PLAYER, BANDITS);
	addHostility(CIVILIANS, BANDITS);
}

bool UFaction::IsFactionHostileToFaction(int32 id1, int32 id2)
{
	correctIds(id1, id2);
	return map[id1][id2];
}

void UFaction::addHostility(int32 id1, int32 id2)
{
	correctIds(id1, id2);
	map[id1][id2] = true;
}

void UFaction::correctIds(int32 & id1, int32 & id2)
{
	if (id2 > id1)
	{
		int32 temp = id2;
		id2 = id1;
		id1 = temp;
	}
}