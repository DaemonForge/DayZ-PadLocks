class CfgPatches
{
  class PadLocks
  {
    requiredAddons[]={ "DZ_Data" }; 
  };
};

class CfgMods
{
  class PadLocks
  {
    name="PadLocks";
    type="mod";
	dependencies[]={ "Game", "World", "Mission" };
	class defs
	{
		class stringtableMods
		{
			files[]={"PadLocks/Stringtable"};
		};
		class gameScriptModule
        {
			value = "";
            files[]={
				"PadLocks/scripts/3_Game"
			};
        };
		class worldScriptModule
        {
            value="";
            files[]={ 
				"PadLocks/scripts/4_World" 
			};
        };
	    class missionScriptModule
        {
            value="";
            files[]={
				"PadLocks/scripts/5_Mission" 
			};
        };
    };
  };
};
class CfgVehicles
{
	class Inventory_Base;
	class Padlock: Inventory_Base
	{
		scope = 2;
		displayName = "$STR_PADLOCKS_PADLOCK_NAME";
		descriptionShort = "$STR_PADLOCKS_PADLOCK_DESC";
		model = "PadLocks\data\Padlock.p3d";
		inventorySlot[] = {
				"Att_CombinationLock",
				"Att_Padlock1",
				"Att_Padlock2",
				"Att_Padlock3",
				"Att_Padlock4",
				"Att_Padlock5",
				"Att_Padlock6",
				"Att_Padlock7",
				"Att_Padlock8",
				"Att_Padlock9",
				"Att_Padlock10",
				"Att_Padlock11",
				"Att_Padlock12"
			};
		itemSize[] = {1,2};
		weight = 650;
		repairableWithKits[] = {86};
		repairCosts[] = {50.0};
		simpleHiddenSelections[] = {
		   "Fence",
		   "Ground"
		};
        hiddenSelections[]=
        {
		   "Fence",
		   "Ground"
        };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 863;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class Padlock_Heavy: Padlock
	{
		scope = 2;
		displayName = "$STR_PADLOCKS_HEAVY_NAME";
		descriptionShort = "$STR_PADLOCKS_HEAVY_DESC";
		model = "PadLocks\data\HD_Padlock.p3d";
		itemSize[] = {2,3};
		weight = 1200;
		repairableWithKits[] = {86};
		repairCosts[] = {100.0};
		simpleHiddenSelections[] = {
		   "Fence",
		   "Ground"
		};
        hiddenSelections[]=
        {
		   "Fence",
		   "Ground"
        };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 2875;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class BoltCutter: Inventory_Base
	{
		scope = 2;
		displayName = "$STR_PADLOCKS_BOLTCUTTER_NAME";
		descriptionShort = "$STR_PADLOCKS_BOLTCUTTER_DESC";
		model = "PadLocks\data\BoltCutters\BoltCutters.p3d";
		itemBehaviour = 2;
		rotationFlags = 4;
		lootCategory = "Tools";
		inventorySlot[] = {"Shoulder","Melee"};
		itemSize[] = {2,5};
		weight = 2600;
		simpleHiddenSelections[] = {
		   "Cutter"
		};
        hiddenSelections[]=
        {
		   "Cutter"
        };
		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 450;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class PadLockRepairKit: Inventory_Base
	{
		scope = 2;
		displayName = "$STR_PADLOCKS_REPAIRKIT_NAME";
		descriptionShort = "$STR_PADLOCKS_REPAIRKIT_DESC";
		model = "PadLocks\data\RepairKit\RepairKit.p3d";
		animClass = "Knife";
		rotationFlags = 17;
		stackedUnit = "percentage";
		quantityBar = 1;
		varQuantityInit = 100.0;
		varQuantityMin = 0.0;
		varQuantityMax = 100.0;
		weight = 1200;
		itemSize[] = {2,3};
		repairKitType = 86;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Stitch
				{
					soundSet = "StitchUpSelf_SoundSet";
					id = 201;
				};
				class pickup
				{
					soundSet = "sewingkit_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "sewingkit_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};

class CfgNonAIVehicles
{
    class ProxyAttachment;

    class ProxyPadlock : ProxyAttachment
    {
        scope = 1;
        InventorySlot="Att_CombinationLock";
        model="\PadLocks\data\Padlock.p3d";
    };
	
};