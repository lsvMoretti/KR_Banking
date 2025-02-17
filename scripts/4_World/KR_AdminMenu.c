class KR_AdminMenu extends UIScriptedMenu
{
    protected bool                      m_IsAdminMenuInitialized = false;
    protected bool                      m_IsAdminMenuOpened;
    protected float                     m_UICooldownTimer;
    protected float                     m_UIUpdateTimer;

    protected Widget                    m_AdminMenu;
    protected Widget                    m_ATMspotlol;
    protected Widget                    m_ServerLogSetting;
    protected Widget                    m_GeneralSetting;
    protected Widget                    m_InsertNewATMCard;
    protected Widget                    m_ClanMenuGeneral;
    protected Widget                    m_ClanListPanel;
    

    protected Widget                    m_ServerGeneralSettings;
    protected Widget                    m_ServerPlayerManager;
    protected Widget                    m_ServerClanManager;
    protected Widget                    m_MiscTab;

    protected Widget                    m_MapCard;
    protected MapWidget                 m_MapWidget;



    protected TextWidget                m_PlayerName;
    protected TextWidget                m_SteamIDBox;
    protected TextWidget                m_ClanIdBox;

    protected TextWidget                m_ClanOwnerID;
    protected TextWidget                m_ClanIDBox2;

    protected TextWidget                m_OnlinePlayers;

    protected EditBoxWidget             m_AtmAmount;
    protected EditBoxWidget             m_Bonus;

    protected EditBoxWidget             m_StarterEdit;
    protected EditBoxWidget             m_MaxATMEdit;
    protected EditBoxWidget             m_ClanCreateCostsEdit;
    protected EditBoxWidget             m_AddPlayerCosts;
    protected EditBoxWidget             m_MaxClanStorageEdit;
    protected EditBoxWidget             m_MaxClanPlayerEdit;
    protected EditBoxWidget             m_SearchWithSteamIDBox;
    protected EditBoxWidget             m_MinTransferEdit;
    protected EditBoxWidget             m_TransferFeesEdit;
    protected EditBoxWidget             m_MinPlayerForRobEdit;
    protected EditBoxWidget             m_MinMoneyForRobEdit;
    protected EditBoxWidget             m_MaxMoneyForRobEdit;
    protected EditBoxWidget             m_SecondsForRobEdit;
    protected EditBoxWidget             m_PaycheckValueEdit;
    protected EditBoxWidget             m_PayCheckMinPlayersEdit;
    protected EditBoxWidget             m_WebHookUrlEdit;
    protected EditBoxWidget             m_SearchPlayerInListBox;
    protected EditBoxWidget             m_ClanTagEdit;
    protected EditBoxWidget             m_ClanNameEdit;
    protected EditBoxWidget             m_OnClanAtmEdit;
    protected EditBoxWidget             m_ClansSearchBarEdit;
    protected EditBoxWidget             m_AddToAllPlayersEdit;



    protected CheckBoxWidget            m_CanBeRobbedCheck;
    protected CheckBoxWidget            m_UseWebhookCheck;
    protected CheckBoxWidget            m_LogDepositCheck;
    protected CheckBoxWidget            m_LogWithdrawCheck;
    protected CheckBoxWidget            m_LogClanDepositCheck;
    protected CheckBoxWidget            m_LogClanWithdrawCheck;



    protected CheckBoxWidget            m_ClanAccountsActiveCheck;
    protected CheckBoxWidget            m_ATMRobActiveCheck;
    protected CheckBoxWidget            m_RobMessageActiveCheck;
    protected CheckBoxWidget            m_PaycheckMessageActiveCheck;
    protected CheckBoxWidget            m_CanAddToFullAccCheck;
    protected CheckBoxWidget            m_NeedBankCardToOpenCheck;
    protected CheckBoxWidget            m_CheckBoxCanRob;


    protected ButtonWidget              m_ServerSettingsButton;
    protected ButtonWidget              m_PlayerManagerButton;
    protected ButtonWidget              m_ClanManagerButton;
    protected ButtonWidget              m_BtnSavePlayerData;
    protected ButtonWidget              m_ReloadButton;
    protected ButtonWidget              m_CloseButton;
    protected ButtonWidget              m_SearchOfflineID;
    protected ButtonWidget              m_OpenInClanManagerButton;
    protected ButtonWidget              m_ShowATMOnMapBtn;
    protected ButtonWidget              m_CloseMapBtn;
    protected ButtonWidget              m_TeleportToATM;
    protected ButtonWidget              m_DeleteATMBtn;
    protected ButtonWidget              m_CloseNewATMCardBtn;
    protected ButtonWidget              m_InsertNewATMBtn;
    protected ButtonWidget              m_InsertNewATMSpawnMainBtn;
    protected ButtonWidget              m_BtnSaveServerConfig;
    protected ButtonWidget              m_JoinClanButton;
    protected ButtonWidget              m_DeleteClanButton;
    protected ButtonWidget              m_RefreshClanInfoButton;
    protected ButtonWidget              m_SaveClanSettingsButton;
    protected ButtonWidget              m_ResetAtmRobs;
    protected ButtonWidget              m_AddToAllPlayersButton;
    protected ButtonWidget              m_MiscButton;
    protected ButtonWidget              m_BtnSearchClan;



    protected ItemPreviewWidget         m_ItemPreviewWidget;
    protected EntityAI                  previewItem;


    protected TextListboxWidget         m_PlayersList;
    protected TextListboxWidget         m_SearchBarPlayers;
    protected TextListboxWidget         m_ATMspots;
    protected TextListboxWidget         m_AvaibleATMClassList;
    protected TextListboxWidget         m_ClanLogsList;
    protected TextListboxWidget         m_ClanList;

    protected ref TStringArray          m_ActiveATMClassNames;

    protected int                       m_LastSelectedPlayerIndex;
    protected int                       m_LastSelectedATMIndex = -1;
    protected int                       m_LastSelectedATMIndex2 = -1;
    protected int                       m_PreviewWidgetRotationX;
	protected int                       m_PreviewWidgetRotationY;
    protected int 				        m_characterScaleDelta;
    protected vector                    m_PreviewWidgetOrientation;	
    protected string                    m_LastTargetsSteamID;

    protected bool                      m_IsSearching;


    protected ref array<ref SearchFilterObject> m_TempSearchList;

    override Widget Init ()
    {

        if(!m_IsAdminMenuInitialized)
        {
            layoutRoot                      =   GetGame().GetWorkspace().CreateWidgets("KR_Banking/GUI/layouts/BankingAdminMenu.layout");

            m_GeneralSetting                =   Widget.Cast(layoutRoot.FindAnyWidget("GroupBoxGernal"));
            m_ATMspotlol                    =   Widget.Cast(layoutRoot.FindAnyWidget("GroupBoxATM"));
            m_ServerLogSetting              =   Widget.Cast(layoutRoot.FindAnyWidget("GroupBoxLogs"));
            m_ServerGeneralSettings         =   Widget.Cast(layoutRoot.FindAnyWidget("PanelTabServerSettings"));
            m_ServerPlayerManager           =   Widget.Cast(layoutRoot.FindAnyWidget("PanelTabPlayerManager"));
            m_ServerClanManager             =   Widget.Cast(layoutRoot.FindAnyWidget("PanelWidgetClanManager"));
            m_MapCard                       =   Widget.Cast(layoutRoot.FindAnyWidget("MapPanel"));
            m_InsertNewATMCard              =   Widget.Cast(layoutRoot.FindAnyWidget("PanelInsertNewATM"));
            m_ClanMenuGeneral               =   Widget.Cast(layoutRoot.FindAnyWidget("GroupBoxClanMenu"));
            m_ClanListPanel                 =   Widget.Cast(layoutRoot.FindAnyWidget("GroupBoxClans"));
            m_MiscTab                       =   Widget.Cast(layoutRoot.FindAnyWidget("PanelWidgetMisc"));


            m_PlayerName                    =   TextWidget.Cast(layoutRoot.FindAnyWidget("PlayerName"));
            m_SteamIDBox                    =   TextWidget.Cast(layoutRoot.FindAnyWidget("SteamIDBox"));
            m_ClanIdBox                     =   TextWidget.Cast(layoutRoot.FindAnyWidget("ClanIDBox"));
            m_ClanOwnerID                   =   TextWidget.Cast(layoutRoot.FindAnyWidget("SteamIDBoxClanOwner"));
            m_ClanIDBox2                    =   TextWidget.Cast(layoutRoot.FindAnyWidget("ClanIDBox1"));
            m_OnlinePlayers                 =   TextWidget.Cast(layoutRoot.FindAnyWidget("OnlinePlayersAmount"));



            m_StarterEdit                   =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Starter"));
            m_MaxATMEdit                    =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Max"));
            m_ClanCreateCostsEdit           =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ClanCosts"));
            m_AddPlayerCosts                =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AddCosts"));
            m_MaxClanStorageEdit            =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MaxClanMoney"));
            m_MaxClanPlayerEdit             =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MaxClanMember"));
            m_MinTransferEdit               =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinTransfer"));
            m_TransferFeesEdit              =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TransferFees"));
            m_MinPlayerForRobEdit           =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinPlayerRob"));
            m_MinMoneyForRobEdit            =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinMoneyRob"));
            m_MaxMoneyForRobEdit            =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MaxMoneyRob"));
            m_SecondsForRobEdit             =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SecondsRob"));
            m_PaycheckValueEdit             =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PaycheckValue"));
            m_PayCheckMinPlayersEdit        =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PaycheckMinPlayers"));
            m_WebHookUrlEdit                =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("WebhookLink"));
            m_AtmAmount                     =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BankOnAtm"));
            m_Bonus                         =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Bonus"));
            m_SearchWithSteamIDBox          =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SearchOfflineBox"));
            m_SearchPlayerInListBox         =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EditBoxPlayersFind"));
            m_ClanTagEdit                   =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ClanTagEdit"));
            m_ClanNameEdit                  =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ClanNameEdit"));
            m_OnClanAtmEdit                 =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BankOnClanAtm"));
            m_ClansSearchBarEdit            =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EditBoxClansFind"));
            m_AddToAllPlayersEdit           =   EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EditBoxWidget0"));




            m_ServerSettingsButton          =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnServerS"));
            m_PlayerManagerButton           =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnPlManager"));
            m_ClanManagerButton             =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClManager"));
            m_BtnSavePlayerData             =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnSavePlayer"));
            m_ReloadButton                  =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClManager4"));
            m_CloseButton                   =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidget0"));
            m_SearchOfflineID               =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnSearchOfflineID"));
            m_OpenInClanManagerButton       =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("OpenInClanManagerBtn"));
            m_ShowATMOnMapBtn               =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ShowATMOnMap"));
            m_CloseMapBtn                   =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidget1"));
            m_TeleportToATM                 =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("TeleportToATM"));
            m_DeleteATMBtn                  =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeleteBtn"));
            m_CloseNewATMCardBtn            =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidget2"));
            m_InsertNewATMBtn               =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnInsertATM"));
            m_InsertNewATMSpawnMainBtn      =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("InsertNewSpawnHere"));
            m_BtnSaveServerConfig           =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClManager3"));
            m_AddToAllPlayersButton         =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidget3"));
            m_ResetAtmRobs                  =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidget4"));
            m_MiscButton                    =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnMisc"));
            m_BtnSearchClan                 =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnSearchClan"));


            m_JoinClanButton                =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("JoinClanButton"));
            m_DeleteClanButton              =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeleteClanButton"));
            m_RefreshClanInfoButton         =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRefreshInfo0"));
            m_SaveClanSettingsButton        =   ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnSaveClanSettings"));


            m_CanBeRobbedCheck              =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CanBeRobbed"));
            m_UseWebhookCheck               =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("UseWebhook"));
            m_LogDepositCheck               =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Log1"));
            m_LogWithdrawCheck              =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Log2"));
            m_LogClanDepositCheck           =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Log3"));
            m_LogClanWithdrawCheck          =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Log4"));
            m_CheckBoxCanRob                =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckBoxCanRob"));

            m_ClanAccountsActiveCheck       =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ClanActive"));
            m_ATMRobActiveCheck             =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AtmRobActive"));
            m_RobMessageActiveCheck         =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RobMessageActive"));
            m_PaycheckMessageActiveCheck    =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PaycheckMessageActive"));
            m_CanAddToFullAccCheck          =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CanAddToFullAccount"));
            m_NeedBankCardToOpenCheck       =   CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("NeedBankCardToOpen"));


            m_PlayersList                   =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxPlayers"));
            m_SearchBarPlayers              =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("EditBoxPlayersFind"));
            m_ATMspots                      =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("AtmSpotList"));
            m_AvaibleATMClassList           =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ATMClassNameList"));
            m_ClanLogsList                  =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ClanLogsList"));
            m_ClanList                      =   TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxClans"));


            m_MapWidget                     =   MapWidget.Cast(layoutRoot.FindAnyWidget("MapWidget0"));

            m_ActiveATMClassNames = new ref TStringArray();
            m_TempSearchList = new ref array<ref SearchFilterObject>;
            m_IsAdminMenuInitialized = true;
        }

        return layoutRoot;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);

        if(m_UICooldownTimer > 0)
            m_UICooldownTimer -= timeslice;
        
        if(m_UIUpdateTimer >= 0.05)
        {
            if(m_LastSelectedPlayerIndex != m_PlayersList.GetSelectedRow())
            {
                if(!m_IsSearching)
                {
                    m_LastSelectedPlayerIndex = m_PlayersList.GetSelectedRow();
                    GetBankingClientAdminManager().RequestPlayerdata(m_LastSelectedPlayerIndex);
                }
                else
                {
                    GetBankingClientAdminManager().RequestPlayerdataWithId(m_TempSearchList.Get(m_LastSelectedPlayerIndex).steam64ID);
                }
            }

            if(m_LastSelectedATMIndex != m_ATMspots.GetSelectedRow())
            {
                m_LastSelectedATMIndex = m_ATMspots.GetSelectedRow();
                if(!GetBankingClientAdminManager().Getservercfg() || !GetBankingClientAdminManager().Getservercfg().ATM || !GetBankingClientAdminManager().Getservercfg().ATM.Get(m_ATMspots.GetSelectedRow())) return;
                bool canSelectATMRobbed = GetBankingClientAdminManager().Getservercfg().ATM.Get(m_ATMspots.GetSelectedRow()).GetCanRobbed();
                m_CanBeRobbedCheck.SetChecked(canSelectATMRobbed);
            }

            if(m_LastSelectedATMIndex2 != m_AvaibleATMClassList.GetSelectedRow())
            {
                m_LastSelectedATMIndex2 = m_AvaibleATMClassList.GetSelectedRow();
                string previewClassName = m_ActiveATMClassNames.Get(m_LastSelectedATMIndex2);
                UpdateItemPreview(previewClassName);
            }

            m_UIUpdateTimer = 0;
        }
        else
        {
            m_UIUpdateTimer += timeslice;
        }
    }

    void UpdatePlayerCard(int AmountOnBank, int BonusAmountOnBank, string PlayersName, string TargetsPlainID, string ClanID)
    {
        m_PlayerName.SetText(PlayersName);
        m_SteamIDBox.SetText(TargetsPlainID);
        m_LastTargetsSteamID = TargetsPlainID;
        m_ClanIdBox.SetText(ClanID);
        m_AtmAmount.SetText(AmountOnBank.ToString());
        m_Bonus.SetText(BonusAmountOnBank.ToString());
    }

    void UpdateItemPreview(string itemType)
	{
        if ( !m_ItemPreviewWidget )
			{
				Widget preview_frame = layoutRoot.FindAnyWidget("ItemPreviewWidget0");

				if ( preview_frame ) 
				{
					float width;
					float height;
					preview_frame.GetSize(width, height);

					m_ItemPreviewWidget = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
				}
			}

			if ( previewItem )
				GetGame().ObjectDelete( previewItem );

			previewItem =  EntityAI.Cast(GetGame().CreateObject( itemType, "0 0 0", true, false, true ));

            m_ItemPreviewWidget.SetItem( previewItem );
			m_ItemPreviewWidget.SetModelPosition( Vector(0,0,0.5) );
			float itemx, itemy;		
			m_ItemPreviewWidget.GetPos(itemx, itemy);
			m_ItemPreviewWidget.SetSize( 1.5, 1.5 );
			m_ItemPreviewWidget.SetPos( -0.225, -0.225 );

    }

    override bool OnChange(Widget w, int x, int y, bool finished)
	{
        switch(w)
        {
            case m_SearchPlayerInListBox:
                SearchPlayer();
                break;
        }
        return super.OnChange(w, x, y, finished);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        switch(w)
        {
            case m_CloseButton:
                CloseAdminMenu();
                break;
            case m_PlayerManagerButton:
                SwitchTab(2);
                break;
            case m_ServerSettingsButton:
                SwitchTab(1);
                break;
            case m_ClanManagerButton:
                SwitchTab(3);
                break;
            case m_MiscButton:
                m_OnlinePlayers.SetText(GetBankingClientManager().GetOnlinePlayers().Count().ToString());
                SwitchTab(4);
                break;
            case m_BtnSavePlayerData:
                HandlePlayerDataSave();
                break;
            case m_ReloadButton:
                GetRPCManager().SendRPC("KR_BANKING", "AdminReloadConfig", null, true);
                break;
            case m_OpenInClanManagerButton:
                string stttttt = GetBankingClientManager().GetOnlinePlayers().Get(m_PlayersList.GetSelectedRow()).plainid;
                GetBankingClientAdminManager().RequestClanDataById(stttttt);
                SwitchTab(3);
                break;
            case m_SearchOfflineID:
                GetBankingClientAdminManager().RequestPlayerdataWithId(m_SearchWithSteamIDBox.GetText());
                break;
            case m_ShowATMOnMapBtn:
                HandleShowATMOnMap();
                break;
            case m_CloseMapBtn:
                m_MapCard.Show(false);
                break;
            case m_TeleportToATM:
                TeleportToATM(m_ATMspots.GetSelectedRow());
                break;
            case m_DeleteATMBtn:
                GetBankingClientAdminManager().DeleteATMWithID(m_ATMspots.GetSelectedRow());
                break;
            case m_CloseNewATMCardBtn:
                m_InsertNewATMCard.Show(false);
                break;
            case m_InsertNewATMBtn:
                HandleInsertNewAtm();
                break;
            case m_InsertNewATMSpawnMainBtn:
                m_InsertNewATMCard.Show(true);
                LoadAllATMs();
                break;
            case m_BtnSaveServerConfig:
                HandleRemoteConfigSave();
                break;
            //New Functions from here on 09.03.2021
            case m_JoinClanButton:
               HandleJoinClan();
                break;
            case m_DeleteClanButton:
                HandleDeleteClan();
                break;
            case m_RefreshClanInfoButton:
               RefreshClanInfo();
                break;
            case m_SaveClanSettingsButton:
               HandleSaveClanSettings();
                break;
            case m_ResetAtmRobs:
                HandleResetAtmRobs();
                break;
            case m_AddToAllPlayersButton:
                HandleAddMoneyToAllPlayers();
                break;
            case m_BtnSearchClan:
                SearchClan();
                break;
            case m_CanBeRobbedCheck:
                GetBankingClientAdminManager().ChangeRobState(m_CanBeRobbedCheck.IsChecked(), m_ATMspots.GetSelectedRow());
                break;
        }

        return super.OnClick(w, x, y, button);
    }


    void HandleRemoteConfigSave()
    {
        ref KR_BankingConfigManager cfg = new KR_BankingConfigManager;
        cfg.ModVersion = GetBankingClientAdminManager().Getservercfg().ModVersion;
        cfg.MenuDelay = GetBankingClientAdminManager().Getservercfg().MenuDelay;
        cfg.startCurrency = m_StarterEdit.GetText().ToInt();
        cfg.maxCurrency = m_MaxATMEdit.GetText().ToInt();
        cfg.IsClanAccountActive = m_ClanAccountsActiveCheck.IsChecked();
        cfg.CostsToCreateClan = m_ClanCreateCostsEdit.GetText().ToInt();
        cfg.CostsToInviteAnPlayer = m_AddPlayerCosts.GetText().ToInt();
        cfg.MaxClanAccountLimit = m_MaxClanStorageEdit.GetText().ToInt();
        cfg.MaxPlayersInClan = m_MaxClanPlayerEdit.GetText().ToInt();
        cfg.MinAmountToTransfer = m_MinTransferEdit.GetText().ToInt();
        cfg.TransferfeesInProcent = m_TransferFeesEdit.GetText().ToInt();
        cfg.IsRobEventActive = m_ATMRobActiveCheck.IsChecked();
        cfg.MinPlayersForRob = m_MinPlayerForRobEdit.GetText().ToInt();
        cfg.MinMoneyForRob = m_MinMoneyForRobEdit.GetText().ToInt();
        cfg.MaxMoneyForRob = m_MaxMoneyForRobEdit.GetText().ToInt();
        cfg.TimeInSecToRobATM = m_SecondsForRobEdit.GetText().ToInt();
        cfg.RobMessagesActive = m_RobMessageActiveCheck.IsChecked();
        cfg.PayCheckValue = m_PaycheckValueEdit.GetText().ToInt();
        cfg.MinPlayersForPayCheck = m_PayCheckMinPlayersEdit.GetText().ToInt();
        cfg.IsPayCheckMessageActive = m_PaycheckMessageActiveCheck.IsChecked();
        cfg.CanAddPayCheckInSafezone = GetBankingClientAdminManager().Getservercfg().CanAddPayCheckInSafezone;
        cfg.CanAddToFullAcc = m_CanAddToFullAccCheck.IsChecked();
        cfg.NeedsBankCardToOpenMenu = m_NeedBankCardToOpenCheck.IsChecked();

        cfg.m_LoggingSettings = GetBankingClientAdminManager().Getservercfg().m_LoggingSettings;
        
        //Hotfix for Paycheck Message is gone. 
        cfg.PayCheckMessage = GetBankingClientAdminManager().Getservercfg().PayCheckMessage;

        //Hotfix for Webhook
        cfg.m_DiscordWebhook.m_LogClanCreateToDiscord = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanCreateToDiscord;
        cfg.m_DiscordWebhook.m_LogClanInviteMemberToDiscord = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanInviteMemberToDiscord;
        cfg.m_DiscordWebhook.m_LogClanRemoveMemberToDiscord = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanRemoveMemberToDiscord;
        cfg.m_DiscordWebhook.m_LogClanUpdatePermissionToDiscord = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanKickMemberToDiscord;
        cfg.m_DiscordWebhook.m_AdminLogUpdateServerConfig = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_AdminLogUpdateServerConfig;
        cfg.m_DiscordWebhook.m_AdminLogUpdatePlayerData = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_AdminLogUpdatePlayerData;
        cfg.m_DiscordWebhook.m_AdminLogUpdateClanData = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_AdminLogUpdateClanData;
        cfg.m_DiscordWebhook.m_AdminLogUseMisc = GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_AdminLogUseMisc;
        
        /* ServerLogs */
        cfg.m_DiscordWebhook.m_UseWebhook = m_UseWebhookCheck.IsChecked();
        cfg.m_DiscordWebhook.m_WebhookURL = m_WebHookUrlEdit.GetText();
        cfg.m_DiscordWebhook.m_LogDepositToDiscord = m_LogDepositCheck.IsChecked();
        cfg.m_DiscordWebhook.m_LogWithdrawToDiscord = m_LogWithdrawCheck.IsChecked();
        cfg.m_DiscordWebhook.m_LogClanDepositToDiscord = m_LogClanDepositCheck.IsChecked();
        cfg.m_DiscordWebhook.m_LogClanWithdrawToDiscord = m_LogClanWithdrawCheck.IsChecked();

        cfg.ATM = GetBankingClientAdminManager().Getservercfg().ATM;
        cfg.BankingCurrency = GetBankingClientAdminManager().Getservercfg().BankingCurrency;

        
        GetBankingClientAdminManager().SendConfigToRemote(cfg);
    }

    //New Clan Manager functions here 08.03.2021 - Hier habe ich weiter gemacht wo du pennen gegangen bist - ist meistens nur die base - du musst den code noch reinmachen schnuggi

    void SearchClan()
    {
        string searchTerm = m_ClansSearchBarEdit.GetText();
        if(searchTerm && searchTerm != "")
        {
            GetBankingClientAdminManager().RequestClanDataById(searchTerm);
        }
        else
        {
            SetFocus(m_ClansSearchBarEdit);//Foucs widget hopefully server owner / admin see this :P
            GetBankingClientManager().SendNotification("ID search param is empty please fill in a ID!");
        }
    }

    void UpdateClanDataCard()
    {
        m_ClanOwnerID.SetText(GetBankingClientAdminManager().m_LastRequestedClanData.GetOwnersID());
        m_OnClanAtmEdit.SetText(GetBankingClientAdminManager().m_LastRequestedClanData.GetBankCredit().ToString());
        m_ClanNameEdit.SetText(GetBankingClientAdminManager().m_LastRequestedClanData.GetName());
        m_ClanTagEdit.SetText(GetBankingClientAdminManager().m_LastRequestedClanData.GetClanTag());
        m_ClanIDBox2.SetText(GetBankingClientAdminManager().m_LastRequestedClanData.GetClanID());


        m_ClanList.ClearItems();
        m_ClanLogsList.ClearItems();

        //Soo easy this system *_*
        for(int i = 0; i < GetBankingClientAdminManager().m_LastRequestedClanData.GetClanMembers().Count(); i++)
        {
            m_ClanList.AddItem(GetBankingClientAdminManager().m_LastRequestedClanData.GetClanMembers().Get(i).GetPlayerName(), NULL, 0)
        }

        foreach(string LogLine : GetBankingClientAdminManager().m_LastRequestedClanData.GetClanLogs())
        {
            m_ClanLogsList.AddItem(LogLine, NULL, 0);
        }
    }

    void HandleJoinClan()
    {
        GetBankingClientAdminManager().JoinLastLoadedClan();
    }

    void HandleDeleteClan()
    {
        GetBankingClientAdminManager().DeleteClan();
    }

    void RefreshClanInfo()
    {

    }

    void HandleAddMoneyToAllPlayers()
    {
        int AmountForDrop = m_AddToAllPlayersEdit.GetText().ToInt();
        GetBankingClientAdminManager().MakeMoneyDrop(AmountForDrop);
    }

    void HandleResetAtmRobs()
    {
        GetBankingClientAdminManager().RequestResetAtmRobs();
    }

    void HandleSaveClanSettings()
    {   
        int newClanBankAmount = m_OnClanAtmEdit.GetText().ToInt();
        string newClanName    = m_ClanNameEdit.GetText();
        string NewClanTag     = m_ClanTagEdit.GetText();
        GetBankingClientAdminManager().UpdateClanData(newClanBankAmount, newClanName, NewClanTag);
    }

    void HandleInsertNewAtm()
    {
        bool CanRob = m_CheckBoxCanRob.IsChecked();
        string ATMClassname = m_ActiveATMClassNames.Get(m_LastSelectedATMIndex2); 
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        vector Position = player.GetPosition();
        vector Orientation = player.GetOrientation();

        GetBankingClientAdminManager().InsertNewATM(ATMClassname, CanRob, Position, Orientation);
    }

    void SearchPlayer()
    {
        m_IsSearching = true;
        string searchTerm = m_SearchPlayerInListBox.GetText();
        if(searchTerm == ""){
            m_IsSearching = false;
            InvokePlayerList();
        }
        searchTerm.ToLower();
        m_PlayersList.ClearItems();
        m_TempSearchList.Clear();
        for(int i = 0; i < GetBankingClientManager().GetOnlinePlayers().Count(); i++)
        {
            string trgname = GetBankingClientManager().GetOnlinePlayers().Get(i).name;
            trgname.ToLower();
            if(trgname.Contains(searchTerm))
            {
                //Add the name to the list & safe the data to a temp class,
                m_PlayersList.AddItem(" " + GetBankingClientManager().GetOnlinePlayers().Get(i).name, NULL, 0);
                m_TempSearchList.Insert(new ref SearchFilterObject(i, GetBankingClientManager().GetOnlinePlayers().Get(i).plainid));
            }
        }
    }

    void TeleportToATM(int SpotIndex)
    {
        vector TeleportEndPoint = GetBankingClientAdminManager().Getservercfg().ATM.Get(SpotIndex).GetATMPosition();
        if(TeleportEndPoint)
            GetBankingClientAdminManager().TeleportToAtm(TeleportEndPoint);
        else
            GetBankingClientManager().SendNotification("CANT FIND ATM POSITION!");
    }

    void HandleShowATMOnMap()
    {
        m_MapCard.Show(true);
        m_MapWidget.ClearUserMarks();

        vector LocalSpawnMarkerPos = GetBankingClientAdminManager().Getservercfg().ATM.Get(m_ATMspots.GetSelectedRow()).GetATMPosition();
		m_MapWidget.AddUserMark(LocalSpawnMarkerPos, "Selected ATM is here", ARGB(255,255,0,0), "\\KR_Banking\\GUI\\textures\\ATMMapicon.paa");
        m_MapWidget.SetScale(0.2);
        SetMapPos(LocalSpawnMarkerPos);

    }
    //Make an Setter idk why its not working on direct call lol.
    void SetMapPos(vector pos)
    {
        m_MapWidget.SetMapPos(pos);
    }

    void HandlePlayerDataSave()
    {
        int newBankAmount = m_AtmAmount.GetText().ToInt();
        int newBankBonus =  m_Bonus.GetText().ToInt();
        //Todo add nullchecks.
        GetBankingClientAdminManager().RequestSavePlayerData(m_LastTargetsSteamID, newBankAmount, newBankBonus);
    }

    void CloseAdminMenu()
    {
        GetGame().GetUIManager().Back();
    }

    void LoadAllATMs()
    {
        m_AvaibleATMClassList.ClearItems();
        m_ActiveATMClassNames.Clear();
        int class_name_count = g_Game.ConfigGetChildrenCount("CfgVehicles");
        for(int i = 0; i < class_name_count; i++)
        {
            string classname;
            GetGame().ConfigGetChildName( "CfgVehicles", i, classname );

            int scopeValue = GetGame().ConfigGetInt( "CfgVehicles" + " " + classname + " scope" );

            if(scopeValue == 0)
                continue;
            
            if(GetGame().IsKindOf(classname,"KR_BankingATM"))//Check if Base class is Banking Base.
            {
                m_AvaibleATMClassList.AddItem(classname, NULL, 0);
                m_ActiveATMClassNames.Insert(classname);
            }
        }
    }

    void SwitchTab(int TabIndex)
    {
        int lastTab;
        if(lastTab == TabIndex)
            return;
        lastTab = TabIndex;
        switch(TabIndex)
        {
            case 1:
                SyncServerSettings();
                m_ServerGeneralSettings.Show(true);
                m_ServerPlayerManager.Show(false);
                m_ServerClanManager.Show(false);
                m_MiscTab.Show(false);
                break;
            case 2:
                m_ServerPlayerManager.Show(true);
                m_ServerClanManager.Show(false);
                m_ServerGeneralSettings.Show(false);
                m_MiscTab.Show(false);
                break;
            case 3:
                m_ServerClanManager.Show(true);
                m_ServerPlayerManager.Show(false);
                m_ServerGeneralSettings.Show(false);
                m_MiscTab.Show(false);
                break;
            case 4:
                m_MiscTab.Show(true);
                m_ServerClanManager.Show(false);
                m_ServerPlayerManager.Show(false);
                m_ServerGeneralSettings.Show(false);

        }
    }

    void InvokePlayerList()
    {
        m_PlayersList.ClearItems();
        for(int i = 0; i < GetBankingClientManager().GetOnlinePlayers().Count(); i++)
        {
            m_PlayersList.AddItem(" " + GetBankingClientManager().GetOnlinePlayers().Get(i).name, NULL, 0);
        }
    }

    bool IsAdminMenuOpen()
    {
        return m_IsAdminMenuOpened;
    }

    void SetIsAdminMenuOpened(bool visiblestate)
    {
        m_IsAdminMenuOpened= visiblestate;
    }

    void SyncServerSettings()
    {
        GetBankingClientAdminManager().GetServerSettings();
    }

    //!Updates the server tab!
    void InitServerSettings()
    {
        /* General Settings */
        m_StarterEdit.SetText(GetBankingClientAdminManager().Getservercfg().startCurrency.ToString());
        m_MaxATMEdit.SetText(GetBankingClientAdminManager().Getservercfg().maxCurrency.ToString());
        m_ClanAccountsActiveCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().IsClanAccountActive);
        m_ClanCreateCostsEdit.SetText(GetBankingClientAdminManager().Getservercfg().CostsToCreateClan.ToString());
        m_AddPlayerCosts.SetText(GetBankingClientAdminManager().Getservercfg().CostsToInviteAnPlayer.ToString());
        m_MaxClanStorageEdit.SetText(GetBankingClientAdminManager().Getservercfg().MaxClanAccountLimit.ToString());
        m_MaxClanPlayerEdit.SetText(GetBankingClientAdminManager().Getservercfg().MaxPlayersInClan.ToString());
        m_MinTransferEdit.SetText(GetBankingClientAdminManager().Getservercfg().MinAmountToTransfer.ToString());
        m_TransferFeesEdit.SetText(GetBankingClientAdminManager().Getservercfg().TransferfeesInProcent.ToString());
        m_ATMRobActiveCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().IsRobEventActive);
        m_MinPlayerForRobEdit.SetText(GetBankingClientAdminManager().Getservercfg().MinPlayersForRob.ToString());
        m_MinMoneyForRobEdit.SetText(GetBankingClientAdminManager().Getservercfg().MinMoneyForRob.ToString());
        m_MaxMoneyForRobEdit.SetText(GetBankingClientAdminManager().Getservercfg().MaxMoneyForRob.ToString());
        m_SecondsForRobEdit.SetText(GetBankingClientAdminManager().Getservercfg().TimeInSecToRobATM.ToString());
        m_RobMessageActiveCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().RobMessagesActive);
        m_PaycheckValueEdit.SetText(GetBankingClientAdminManager().Getservercfg().PayCheckValue.ToString());
        m_PayCheckMinPlayersEdit.SetText(GetBankingClientAdminManager().Getservercfg().MinPlayersForPayCheck.ToString());
        m_PaycheckMessageActiveCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().IsPayCheckMessageActive);
        m_CanAddToFullAccCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().CanAddToFullAcc);
        m_NeedBankCardToOpenCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().NeedsBankCardToOpenMenu);

        /* Server Log Settings */
        m_UseWebhookCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_UseWebhook);
        m_WebHookUrlEdit.SetText(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_WebhookURL);
        m_LogDepositCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogDepositToDiscord);
        m_LogWithdrawCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogWithdrawToDiscord);
        m_LogClanDepositCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanDepositToDiscord);
        m_LogClanWithdrawCheck.SetChecked(GetBankingClientAdminManager().Getservercfg().m_DiscordWebhook.m_LogClanWithdrawToDiscord);

        /* ATM */
        //AtmSpotList m_ATMspots
        m_ATMspots.ClearItems();
        for(int i = 0; i < GetBankingClientAdminManager().Getservercfg().ATM.Count(); i++)
        {
            m_ATMspots.AddItem(" " + GetBankingClientAdminManager().Getservercfg().ATM.Get(i).ATMSName, NULL, 0);
        }
    }

    override void OnShow()
	{
        GetBankingClientManager().RequestOnlinePlayers(true);

		super.OnShow();

		PPEffects.SetBlurMenu(0.5);

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);

        GetGame().GetUIManager().ShowUICursor( true );
	}

    override void OnHide()
	{
		super.OnHide();

		PPEffects.SetBlurMenu(0);

		GetGame().GetInput().ResetGameFocus();

		GetGame().GetMission().PlayerControlEnable(false);

        GetGame().GetUIManager().ShowUICursor( false );

        SetIsAdminMenuOpened( false );

		Close();
	}

    bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		super.OnMouseButtonDown(w, x, y, button);
		
		if (w == m_ItemPreviewWidget)
		{
			GetGame().GetDragQueue().Call(this, "UpdateRotation");
			g_Game.GetMousePos(m_PreviewWidgetRotationX, m_PreviewWidgetRotationY);
			return true;
		}
		return false;
	}

    void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
	{
		vector o = m_PreviewWidgetOrientation;
		o[0] = o[0] + (m_PreviewWidgetRotationY - mouse_y);
		o[1] = o[1] - (m_PreviewWidgetRotationX - mouse_x);
		
		m_ItemPreviewWidget.SetModelOrientation( o );
		
		if (!is_dragging)
		{
			m_PreviewWidgetOrientation = o;
		}
	}

    override bool OnMouseWheel(Widget  w, int  x, int  y, int wheel)
	{
		super.OnMouseWheel(w, x, y, wheel);
		
		if ( w == m_ItemPreviewWidget )
		{
			m_characterScaleDelta = wheel;
			UpdateScale();
		}
		return false;
	}

    void UpdateScale()
	{
		float w, h, x, y;		
		m_ItemPreviewWidget.GetPos(x, y);
		m_ItemPreviewWidget.GetSize(w,h);
		w = w + ( m_characterScaleDelta / 4);
		h = h + ( m_characterScaleDelta / 4 );
		if ( w > 0.5 && w < 3 )
		{
			m_ItemPreviewWidget.SetSize( w, h );
			int screen_w, screen_h;
			GetScreenSize(screen_w, screen_h);
			float new_x = x - ( m_characterScaleDelta / 8 );
			float new_y = y - ( m_characterScaleDelta / 8 );
			m_ItemPreviewWidget.SetPos( new_x, new_y );
		}
	}
};