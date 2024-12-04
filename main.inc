/*******************************************************************************
* FILENAME :        main.inc
*
* DESCRIPTION :
*       Linkage of all modules and includes, definiton of values.
*
* NOTES :
*       This file is not intended to handle player's functions or anything.
*       This file must only have links and constants.
*
*       Copyright MenduS12 2024.  All rights reserved.
*/

// Required to be at the top
#include <open.mp>
#include <a_mysql>
#include <sscanf2>
#include <foreach>
#include <Pawn.CMD>
#include <Pawn.RakNet>

#include "modules/colors.inc"


#define MYSQL_HOST "localhost"
#define MYSQL_PASS ""
#define MYSQL_USER "root"
#define MYSQL_DBSE "basic"

#define function%0(%1) forward%0(%1); public%0(%1)

#define SERVER_VERSION "v1.0b"

#define InfoMessage(%0,%1) 	SendClientMessage(%0, COLOR_SERVER, "Notice: "COL_WHITE""%1)
#define UsageMessage(%0,%1) SendClientMessage(%0, COLOR_ORANGE, "Usage: "COL_WHITE""%1)
#define ErrorMessage(%0,%1) SendClientMessage(%0, COLOR_RED, "Error: "COL_WHITE""%1)

new MySQL:SQL;

enum PlayerData
{
	sID,
	pName[MAX_PLAYER_NAME],
	pPassword,
	pMoney,
	pSkin,
	pLevel,

	//==== not save 
	bool:pLoggedIn
};
new pData[MAX_PLAYERS][PlayerData];

enum
{
	DIALOG_UNUSED,
	DIALOG_REGISTER,
	DIALOG_LOGIN,
}

new CmdTime[MAX_PLAYERS];

/*
     ___      _
    / __| ___| |_ _  _ _ __
    \__ \/ -_)  _| || | '_ \
    |___/\___|\__|\_,_| .__/
                      |_|
*/

GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

GetPName(playerid)
{
	GetPlayerName(playerid, pData[playerid][pName], MAX_PLAYER_NAME);
	return pData[playerid][pName];
}



main()
{
	printf(" ");
	printf("  ----------------------------------------");
	printf("  |  Basic Regis/login open.mp gamemode! |");
	printf("  ----------------------------------------");
	printf(" ");
}

public OnGameModeInit()
{
	print("[MySQL] Connecting to database...");
	SQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DBSE);	
	if(mysql_errno(SQL) != 0)
	{
		print("[MySQL] Connect to database unsuccesful.");
		return 0;
	}
	
	
	SetGameModeText(""SERVER_VERSION"");
	DisableInteriorEnterExits();
	return 1;
}

public OnGameModeExit()	
{
	foreach(new i : Player)
	{
		if(pData[i][pLoggedIn]) SavePlayer(i);
	}
	mysql_close(SQL);
	return 1;
}

/*
      ___
     / __|___ _ __  _ __  ___ _ _
    | (__/ _ \ '  \| '  \/ _ \ ' \
     \___\___/_|_|_|_|_|_\___/_||_|

*/

public OnPlayerConnect(playerid)
{
	GetPName(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(pData[playerid][pLoggedIn]) SavePlayer(playerid);
	pData[playerid][pLoggedIn] = false;
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	InterpolateCameraPos(playerid, 1039.624511, -1955.488037, 227.646926, 1479.973632, -2255.286376, 50.983421, 15000);
	InterpolateCameraLookAt(playerid, 1043.405029, -1958.182128, 225.789596, 1475.610107, -2252.845214, 50.968055, 1000);
	if(!pData[playerid][pLoggedIn])
	{
		new query[128];
		mysql_format(SQL, query, sizeof(query), "SELECT id FROM players WHERE name = '%e'", pData[playerid][pName]);
		mysql_pquery(SQL, query, "OnUserCheck", "d", playerid);
	}
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerInterior(playerid, 0);
	TogglePlayerControllable(playerid, true);

	SetPlayerPos(playerid, -2407.2300,516.3400,30.3828);

	GivePlayerMoney(playerid, pData[playerid][pMoney]);
	SetPlayerSkin(playerid, pData[playerid][pSkin]);

	return 1;
}

public OnPlayerDeath(playerid, killerid, WEAPON:reason)
{
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

function OnUserCheck(playerid)
{
	SetTimerEx("AutoKick", 60 * 1000, false, "i", playerid);
	new rows;
	cache_get_row_count(rows);
	if(rows == 0)
	{
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, ""COL_SERVER"Basic Register,Login OpenMP"COL_WHITE"- Register", "[EN] Welcome to "COL_SERVER"Basic Register,Login OpenMP"COL_WHITE",\nPlease enter the password to register your account", "Register", "Exit");
	}
	else
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, ""COL_SERVER"Basic Register,Login OpenMP"COL_WHITE"- Login", "[EN] Welcome back to "COL_SERVER"Basic Register,Login OpenMP"COL_WHITE",\nPlease enter the password to log in to your account", "Login", "Exit");
	}
	return 1;
}

/*
     ___              _      _ _    _
    / __|_ __  ___ __(_)__ _| (_)__| |_
    \__ \ '_ \/ -_) _| / _` | | (_-<  _|
    |___/ .__/\___\__|_\__,_|_|_/__/\__|
        |_|
*/

public OnFilterScriptInit()
{
	printf(" ");
	printf("  -----------------------------------------");
	printf("  |  Error: Script was loaded incorrectly |");
	printf("  -----------------------------------------");
	printf(" ");
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys)
{
	return 1;
}

public OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, WEAPON:weaponid, bodypart)
{
	return 1;
}

public OnActorStreamIn(actorid, forplayerid)
{
	return 1;
}

public OnActorStreamOut(actorid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_REGISTER)
	{
		if(!response) return Kick(playerid);
		if(strlen(inputtext) < 4 || strlen(inputtext) > 24)
		{
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, ""COL_SERVER" "COL_WHITE"- Register", "[EN] Welcome to "COL_SERVER"Basic Register,Login OpenMP"COL_WHITE",\nPlease enter the password to register your account", "Register", "Exit");
            ErrorMessage(playerid, "Your password must more than 4 words and no more than 24 words");
            return 1;
		}

		new query[256];
		mysql_format(SQL, query, sizeof(query), "INSERT INTO players (Name, Password) VALUES ('%e', MD5('%e'))", pData[playerid][pName], inputtext);
		mysql_pquery(SQL, query, "OnUserRegister", "d", playerid);
		return 1;
	}
	if(dialogid == DIALOG_LOGIN)
	{
		if(strlen(inputtext) < 4 || strlen(inputtext) > 24)
		{
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, ""COL_SERVER" "COL_WHITE"- Login", "[EN] Welcome back to "COL_SERVER"Basic Register,Login OpenMP"COL_WHITE",\nPlease enter the password to log in to your account", "Login", "Exit");
            ErrorMessage(playerid, "Your password must more than 4 words and no more than 24 words");
            return 1;
		}

		new query[256];
		mysql_format(SQL, query, sizeof(query), "SELECT * FROM players WHERE name = '%e' AND Password = MD5('%e')", pData[playerid][pName], inputtext);
		mysql_pquery(SQL, query, "OnUserLogin", "d", playerid);
		return 1;
	}
	return 1;
}

public OnPlayerEnterGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerLeaveGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerEnterPlayerGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerLeavePlayerGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerClickGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerClickPlayerGangZone(playerid, zoneid)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	return 1;
}

public OnPlayerRequestDownload(playerid, DOWNLOAD_REQUEST:type, crc)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 0;
}

public OnPlayerSelectObject(playerid, SELECT_OBJECT:type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{
	return 1;
}

public OnPlayerEditObject(playerid, playerobject, objectid, EDIT_RESPONSE:response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	return 1;
}

public OnPlayerEditAttachedObject(playerid, EDIT_RESPONSE:response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnPlayerPickUpPlayerPickup(playerid, pickupid)
{
	return 1;
}

public OnPickupStreamIn(pickupid, playerid)
{
	return 1;
}

public OnPickupStreamOut(pickupid, playerid)
{
	return 1;
}

public OnPlayerPickupStreamIn(pickupid, playerid)
{
	return 1;
}

public OnPlayerPickupStreamOut(pickupid, playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, WEAPON:weaponid, bodypart)
{
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, WEAPON:weaponid, bodypart)
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, CLICK_SOURCE:source)
{
	return 1;
}

public OnPlayerWeaponShot(playerid, WEAPON:weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	return 1;
}

public OnTrailerUpdate(playerid, vehicleid)
{
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	return 1;
}

function OnUserRegister(playerid)
{
	pData[playerid][sID] = cache_insert_id();
	pData[playerid][pLoggedIn]  = true;
	SpawnPlayer(playerid);
	SendClientMessage(playerid, COLOR_SERVER, " "COL_WHITE"-> Welcome "COL_SERVER"%s!, "COL_WHITE"hope you enjoy playing in Flash Deathmatch.", GetName(playerid));
	return 1;
}

function OnUserLogin(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows == 0)
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, ""COL_SERVER" "COL_WHITE"- Login", "[EN] Welcome back to "COL_SERVER"Basic Register,Login OpenMP"COL_WHITE",\nPlease enter the password to log in to your account", "Login", "Exit");
		ErrorMessage(playerid, "You input wrong password!");
	}
	else
	{
		cache_get_value_name_int(0, "ID", pData[playerid][sID]);
		cache_get_value_name_int(0, "Money", pData[playerid][pMoney]);
		cache_get_value_name_int(0, "Skin", pData[playerid][pSkin]);
		cache_get_value_name_int(0, "Level", pData[playerid][pLevel]);
		pData[playerid][pLoggedIn]  = true;
		SpawnPlayer(playerid);
		SendClientMessage(playerid, COLOR_SERVER, " "COL_WHITE"-> Welcome back "COL_SERVER"%s!, "COL_WHITE"hope you enjoy learing Pawn :).", GetName(playerid));
	}
	return 1;
}

function AutoKick(playerid) 
{
	if(pData[playerid][pLoggedIn]) return 1;
	InfoMessage(playerid, "60 seconds pass, you are being automaticly kicked.");
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if(result == -1)
	{
		ErrorMessage(playerid, "Command that you typed doesn't exist. {FFFF00}/help"COL_WHITE"");
		return 0;
	}
	return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if(!pData[playerid][pLoggedIn])
	{
		ErrorMessage(playerid, "You must login to use commands.");
		return 0;
	}
	if(CmdTime[playerid] > gettime())
	{
		ErrorMessage(playerid, "Calm down, don't spamming");
		return 0;
	}
	return 1;
}

CMD:setskin(playerid, params[])
{
	new targetid, skin;
	if(sscanf(params, "ui", targetid, skin)) 
		return UsageMessage(playerid, "/setskin [playerid, 0 - 299]");

	if(skin < 1 || skin > 299) 
		return ErrorMessage(playerid, "Invalid skin! [ 0 - 299 ]");
		
	pData[playerid][pSkin] = skin;
	SetPlayerSkin(targetid, pData[playerid][pSkin]);
   	return 1;
}
//========================================================FORWARDS

forward LoadPlayer(playerid);
public LoadPlayer(playerid)
{
	if(cache_num_rows() > 0)
	{
		cache_get_value_int(0, "ID", pData[playerid][sID]);
		cache_get_value_int(0, "Money", pData[playerid][pMoney]);
		cache_get_value_int(0, "Skin", pData[playerid][pSkin]);
		cache_get_value_int(0, "Level", pData[playerid][pLevel]);
		SendClientMessage(playerid, -1, "Player Data Load");
	}
	return 1;
}

//========================================================Stock
stock SavePlayer(playerid)
{
	if(pData[playerid][pLoggedIn])
	{
		new query[1000];
		mysql_format(SQL, query, sizeof(query), "UPDATE `players` SET `Money` = %d, `Skin` = %d, `Level` = %d WHERE `ID` = %d",
		pData[playerid][pMoney],
		pData[playerid][pSkin], 
		pData[playerid][pLevel],
		pData[playerid][sID]);
	
		mysql_tquery(SQL, query);
		printf("[MySQL] Saved %s's data", pData[playerid][pName]);
	}
	return 1;
}