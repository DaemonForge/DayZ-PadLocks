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
    type="mod"
	dependencies[]={ "Game", "World", "Mission" };
	class defs
	{
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
		displayName = "PadLock";
		descriptionShort = "A simple PadLock for locking your shit up";
		model = "PadLocks\data\Padlock.p3d";
		inventorySlot[] = {"Att_CombinationLock"};
		itemSize[] = {1,2};
		weight = 350;
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
					hitpoints = 750;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class Padlock_Heavy: Padlock
	{
		scope = 2;
		displayName = "Heavy PadLock";
		descriptionShort = "A Heavy Duty PadLock for locking your shit up";
		model = "PadLocks\data\HD_Padlock.p3d";
		inventorySlot[] = {"Att_CombinationLock"};
		itemSize[] = {2,3};
		weight = 500;
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
					hitpoints = 2000;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class BoltCutter: Inventory_Base
	{
		scope = 2;
		displayName = "BoltCutter";
		descriptionShort = "A Bolt Cutter could be used to cut PadLocks";
		model = "PadLocks\data\BoltCutters\BoltCutters.p3d";
		itemBehaviour = 2;
		rotationFlags = 4;
		lootCategory = "Tools";
		inventorySlot[] = {"Shoulder","Melee"};
		itemSize[] = {2,5};
		weight = 1100;
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
					hitpoints = 500;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
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