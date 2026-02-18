class PadlockConfig extends Managed {

    protected static string ConfigDIR = "$profile:Padlock";
    protected static string ConfigPATH = ConfigDIR + "\\config.json";
    static ref PadlockConfig m_Config;
    string ConfigVersion = "0";
	int Enable6NumberCodes = 0;
	autoptr TStringArray RaidBlockList = {"SOMETHING"};
	
    void Load(){
        if (GetGame().IsServer()){
            if (FileExist(ConfigPATH)){ // If config exist load File
                JsonFileLoader<PadlockConfig>.JsonLoadFile(ConfigPATH, this);
            } else { // File does not exist create file    
                MakeDirectory(ConfigDIR);
                Save();
            }
        }
    }
    void Save(){
        JsonFileLoader<PadlockConfig>.JsonSaveFile(ConfigPATH, this);
    }
	
	static bool CanRaid(string type){
		type.ToLower();
		for (int i = 0 ; i < m_Config.RaidBlockList.Count(); i++) {
			string toCompare = m_Config.RaidBlockList.Get(i);
			toCompare.ToLower();
			if (type == toCompare) return false;
		}
		return true;
	}
	
	static bool Is6DigitEnabled(){
		if (m_Config && m_Config.Enable6NumberCodes == 1){
			return true;
		}
		return false;
	}
}
//Helper function to return Config
static PadlockConfig GetPadlockConfig()
{
    if ( GetGame().IsServer() ){
        if (!PadlockConfig.m_Config)
        {
            PadlockConfig.m_Config = new PadlockConfig;
            PadlockConfig.m_Config.Load();
        }
    }
    return PadlockConfig.m_Config;
};  