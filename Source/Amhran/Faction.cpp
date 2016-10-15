// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Faction.h"

UFaction::UFaction()
{
	//map.SetNum(NUMFACTIONS);
	for(int i = 0; i < NUMFACTIONS; i++)
	{
		map.Add(FInnerMap());
		//map[i].imap.SetNum(NUMFACTIONS);
		for(int ii = 0; ii <= i; ii++)
		{
			map[i].imap.Add(false);
		}
	}
	/*------------------
	* Add Hostilities Here!!!!
	------------------*/
	addHostility((int32)(EFactions::PLAYER), (int32)(EFactions::BANDITS));
	addHostility((int32)(EFactions::CIVILIANS), (int32)(EFactions::BANDITS));
}

bool UFaction::IsFactionHostileToFaction(int32 id1, int32 id2)
{
	correctIds(id1, id2);
	return map[id1].imap[id2];
}

void UFaction::addHostility(int32 id1, int32 id2)
{
	correctIds(id1, id2);
	map[id1].imap[id2] = true;
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