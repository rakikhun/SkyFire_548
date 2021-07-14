/* Skip Death Knight Module
   Original Module From Single Player Project Consolidated Skip Module
   Rewritten for TC 434 By Single Player Project Developer MDic
   Original Concept from conanhun513
   Refactored for SkyFire 5.4.8 by Crypticaz
*/

#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Common.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "SharedDefines.h"
#include "World.h"
#include "WorldSession.h"

struct PlayerItemsEntry
{
    PlayerItemsEntry() :
        shoulders(0), chest(0), trinkett(0), weapon(0), weapon2(0), weapon3(0), shield(0),
        shoulders2(0), chest2(0), trinkett2(0), bag(0)
    {
    }

    uint32 shoulders;
    uint32 chest;
    uint32 trinkett;
    uint32 weapon;
    uint32 weapon2;
    uint32 weapon3;
    uint32 shield;
    uint32 shoulders2;
    uint32 chest2;
    uint32 trinkett2;
    uint32 bag;
};

struct ItemCount
{
    ItemCount() :
        shoulderCount(0), chestCount(0), trinkettCount(0), weaponCount(0), weapon2Count(0), weapon3Count(0), shieldCount(0),
        shoulders2Count(0), chest2Count(0), trinkett2Count(0), bagCount(0)
    {
    
    }
    uint32 shoulderCount;
    uint32 chestCount;
    uint32 trinkettCount;
    uint32 weaponCount;
    uint32 weapon2Count;
    uint32 weapon3Count;
    uint32 shieldCount;
    uint32 shoulders2Count;
    uint32 chest2Count;
    uint32 trinkett2Count;
    uint32 bagCount;
};

void AddItem(Player* player, PlayerItemsEntry items, ItemCount count)
{
    player->AddItem(items.shoulders, count.shoulderCount);
    player->AddItem(items.chest, count.chestCount);
    player->AddItem(items.trinkett, count.trinkettCount);
    player->AddItem(items.weapon, count.weaponCount);
    player->AddItem(items.weapon2, count.weapon2Count);
    player->AddItem(items.weapon3, count.weapon3Count);
    player->AddItem(items.shield, count.shieldCount);
    player->AddItem(items.shoulders2, count.shoulders2Count);
    player->AddItem(items.chest2, count.chest2Count);
    player->AddItem(items.trinkett2, count.trinkett2Count);

    // don't want to add 0 or negative bag count
    if (count.bagCount > 0)
        for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
            player->EquipNewItem(i, items.bag, true);
}

class SPP_skip_deathknight_announce : public PlayerScript
{
public:
    SPP_skip_deathknight_announce() : PlayerScript("SPP_skip_deathknight_announce") { }

    void OnLogin(Player* Player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Starter.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00SPP Skip Deathknight Starter |rmodule.");
        }
    }
};

class SPP_skip_deathknight : public PlayerScript
{
public:
    SPP_skip_deathknight() : PlayerScript("SPP_skip_deathknight") { }

    void OnLogin(Player* player, bool firstLogin) override
    {
        int DKL = sConfigMgr->GetFloatDefault("Skip.Deathknight.Start.Level", 58);

        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Starter.Enable", true))
        {
            if (player->GetAreaId() == 4342)
            {
                if (!firstLogin)
                    return;
                player->SetLevel(DKL);
                player->learnSpell(53428, false);//runeforging
                player->learnSpell(53441, false);//runeforging
                player->learnSpell(53344, false);//runeforging
                player->learnSpell(62158, false);//runeforging
                player->learnSpell(33391, false);//journeyman riding
                player->learnSpell(54586, false);//runeforging credit
                player->learnSpell(48778, false);//acherus deathcharger
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

                if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//The Might Of The Scourge
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
                }
                if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//The Light of Dawn
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
                }
                if (player->GetTeam() == ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)//Where Kings Walk
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeam() == HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                if (player->GetTeam() == ALLIANCE)
                    player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f);//Stormwind
                else
                    player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f);//Orgrimmar
                ObjectAccessor::SaveAllPlayers();//Save
            }
        }

        if (sConfigMgr->GetBoolDefault("GM.Skip.Deathknight.Starter.Enable", true))
        {
            if (player->GetSession()->GetSecurity() >= AccountTypes::SEC_MODERATOR && player->GetAreaId() == 4342)
            {
                if (!firstLogin)
                    return;
                player->SetLevel(DKL);
                player->learnSpell(53428, false);//runeforging
                player->learnSpell(53441, false);//runeforging
                player->learnSpell(53344, false);//runeforging
                player->learnSpell(62158, false);//runeforging
                player->learnSpell(33391, false);//journeyman riding
                player->learnSpell(54586, false);//runeforging credit
                player->learnSpell(48778, false);//acherus deathcharger
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

                if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//The Might Of The Scourge
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
                }
                if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//The Light of Dawn
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
                }
                if (player->GetTeam() == ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)//Where Kings Walk
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeam() == HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                if (player->GetTeam() == ALLIANCE)
                    player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f);//Stormwind
                else
                    player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f);//Orgrimmar
                ObjectAccessor::SaveAllPlayers();//Save
            }
        }
    }
};

class spp_skip_worgen : public PlayerScript
{
public:
    spp_skip_worgen() : PlayerScript("spp_skip_worgen") { }

    void OnLogin(Player* Player, bool firstLogin) override
    {
        int WGL = sConfigMgr->GetFloatDefault("Skip.Worgen.Start.Level", 18);

        if (sConfigMgr->GetBoolDefault("Skip.Worgen.Starter.Enable", true))
        {
            if (Player->GetMapId() == 654)
            {
                if (!firstLogin)
                    return;
                Player->learnSpell(72792, false); // Learn Racials
                Player->learnSpell(72857, false); // Learn Two Forms
                Player->learnSpell(95759, false); // Learn Darkflight
                Player->TeleportTo(1, 8181.060059f, 999.103027f, 7.253240f, 6.174160f);
                Player->SetLevel(WGL);
                ObjectAccessor::SaveAllPlayers();
            }
        }

        if (sConfigMgr->GetBoolDefault("GM.Skip.Worgen.Starter.Enable", true))
        {
            if (Player->GetSession()->GetSecurity() >= AccountTypes::SEC_MODERATOR&& Player->GetMapId() == 654)
            {
                if (!firstLogin)
                    return;
                Player->learnSpell(72792, false); // Learn Racials
                Player->learnSpell(72857, false); // Learn Two Forms
                Player->learnSpell(95759, false); // Learn Darkflight
                Player->TeleportTo(1, 8181.060059f, 999.103027f, 7.253240f, 6.174160f);
                Player->SetLevel(WGL);
                ObjectAccessor::SaveAllPlayers();
            }
        }
    }
};

class SPP_skip_worgen_announce : public PlayerScript
{
public:
    SPP_skip_worgen_announce() : PlayerScript("SPP_skip_worgen_announce") { }

    void OnLogin(Player* Player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("Skip.Worgen.Starter.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00SPP Skip Worgen Starter |rmodule.");
        }
    }
};


class spp_skip_goblin : public PlayerScript
{
public:
    spp_skip_goblin() : PlayerScript("spp_skip_goblin") { }

    void OnLogin(Player* Player, bool firstLogin) override
    {
        int GBL = sConfigMgr->GetFloatDefault("Skip.Goblin.Start.Level", 16);

        if (sConfigMgr->GetBoolDefault("Skip.Goblin.Starter.Enable", true))
        {
            if (Player->GetMapId() == 648)
            {
                if (!firstLogin)
                    return;
                Player->SetLevel(GBL);
                Player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f);
                if (Player->GetQuestStatus(25267) == QUEST_STATUS_NONE)
                {
                    Player->AddQuest(sObjectMgr->GetQuestTemplate(25267), NULL);//Message for Garrosh
                }
                ObjectAccessor::SaveAllPlayers();
            }
        }

        if (sConfigMgr->GetBoolDefault("GM.Skip.Goblin.Starter.Enable", true))
        {
            if (Player->GetSession()->GetSecurity() >= AccountTypes::SEC_MODERATOR && Player->GetMapId() == 648)
            {
                if (!firstLogin)
                    return;
                Player->SetLevel(GBL);
                Player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f);
                if (Player->GetQuestStatus(25267) == QUEST_STATUS_NONE)//Message for Garrosh
                {
                    Player->AddQuest(sObjectMgr->GetQuestTemplate(25267), NULL);
                }
                ObjectAccessor::SaveAllPlayers();
            }
        }
    }
};

class SPP_skip_goblin_announce : public PlayerScript
{
public:
    SPP_skip_goblin_announce() : PlayerScript("SPP_skip_goblin_announce") { }

    void OnLogin(Player* Player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("Skip.Goblin.Starter.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00SPP Skip Goblin Starter |rmodule.");
        }
    }
};

class SPP_skip_pandaren : public PlayerScript
{
public:
    SPP_skip_pandaren() : PlayerScript("spp_skip_pandaren") { }

    void OnLogin(Player* player, bool firstLogin) override
    {
        int PL = sConfigMgr->GetFloatDefault("Skip.pandaren.Start.Level", 12);

        if (sConfigMgr->GetBoolDefault("Skip.Pandaren.Starter.Enable", true))
        {
            if (player->GetAreaId() == 5834)
            {
                if (!firstLogin)
                    return;

                player->SetLevel(PL);
                player->ShowNeutralPlayerFactionSelectUI();

                PlayerClass(player);

                ObjectAccessor::SaveAllPlayers(); //Save
            }
        }
        
        if (sConfigMgr->GetBoolDefault("GM.Skip.Pandaren.Starter.Enable", true))
        {
            if (player->GetAreaId() == 5834)
            {
                if (!firstLogin)
                    return;

                player->SetLevel(PL);
                player->ShowNeutralPlayerFactionSelectUI();

                PlayerClass(player);

                ObjectAccessor::SaveAllPlayers(); //Save
            }
        }
    }

    void PlayerClass(Player* player)
    {
        PlayerItemsEntry items;
        ItemCount count;

        items.bag = 41600;
        count.bagCount = 4;
        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                //Warrior
                // items
                items.shoulders = 93893;
                items.chest = 93892;
                items.trinkett = 42991;
                items.weapon = 69893;
                items.shield = 93902;
                items.shoulders2 = 42949;
                items.chest2 = 48685;
                items.weapon2 = 42943;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.shieldCount = 1;
                count.shoulders2Count = 1;
                count.chest2Count = 1;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_PALADIN:
                //Paladin
                // items
                items.shoulders = 69890;
                items.chest = 69889;
                items.trinkett = 42991;
                items.weapon = 69893;
                items.shield = 93902;
                items.shoulders2 = 42951;
                items.chest2 = 48683;
                items.trinkett2 = 42992;
                items.weapon2 = 42948;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.shieldCount = 1;
                count.shoulders2Count = 1;
                count.chest2Count = 1;
                count.trinkett2Count = 2;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_HUNTER:
                //Hunter
                // items
                items.shoulders = 42950;
                items.chest = 48677;
                items.trinkett = 42991;
                items.weapon = 42943;
                items.weapon2 = 42946;
                items.weapon3 = 44093;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.weapon2Count = 1;
                count.weapon3Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_ROGUE:
                //Rogue
                // items
                items.shoulders = 42952;
                items.chest = 48689;
                items.trinkett = 42991;
                items.weapon = 42944;
                items.weapon2 = 42944;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_PRIEST:
                //Priest
                // items
                items.shoulders = 42985;
                items.chest = 48691;
                items.trinkett = 42992;
                items.weapon = 42947;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                AddItem(player, items, count);
                break;
            case CLASS_DEATH_KNIGHT:
                //Death Knight
                // items
                items.shoulders = 42949;
                items.chest = 48685;
                items.trinkett = 42991;
                items.weapon = 42945;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                AddItem(player, items, count);
                break;
            case CLASS_SHAMAN:
                //Shaman
                // items
                items.shoulders = 44102;
                items.chest = 48683;
                items.trinkett = 42992;
                items.weapon = 44064;
                items.shield = 93903;
                items.shoulders2 = 44101;
                items.chest2 = 48677;
                items.weapon2 = 48716;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.shieldCount = 1;
                count.shoulders2Count = 1;
                count.chest2Count = 1;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_MAGE:
                //Mage
                // items
                items.shoulders = 42985;
                items.chest = 48691;
                items.trinkett = 42992;
                items.weapon = 42947;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                AddItem(player, items, count);
                break;
            case CLASS_WARLOCK:
                //Warlock
                // items
                items.shoulders = 42985;
                items.chest = 48691;
                items.trinkett = 42992;
                items.weapon = 42947;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                AddItem(player, items, count);
                break;
            case CLASS_DRUID:
                //Druid
                // items
                items.shoulders = 42984;
                items.chest = 48687;
                items.trinkett = 42992;
                items.weapon = 42948;
                items.shoulders2 = 42952;
                items.chest2 = 48689;
                items.trinkett2 = 42991;
                items.weapon2 = 48718;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.shoulders2Count = 1;
                count.chest2Count = 1;
                count.trinkett2Count = 2;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            case CLASS_MONK:
                //Monk
                // items
                items.shoulders = 42984;
                items.chest = 48687;
                items.trinkett = 42992;
                items.weapon = 42947;
                items.shoulders2 = 42952;
                items.chest2 = 48689;
                items.trinkett2 = 42991;
                items.weapon2 = 48716;
                // item count
                count.shoulderCount = 1;
                count.chestCount = 1;
                count.trinkettCount = 2;
                count.weaponCount = 1;
                count.shoulders2Count = 1;
                count.chest2Count = 1;
                count.trinkett2Count = 2;
                count.weapon2Count = 1;
                AddItem(player, items, count);
                break;
            default:
                break;
        }
    }
};

class SPP_skip_pandaren_announce : public PlayerScript
{
public:
    SPP_skip_pandaren_announce() : PlayerScript("SPP_skip_pandaren_announce") { }

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("Skip.Pandaren.Starter.Announce.enable", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00SPP Skip Pandaren Starter |rmodule.");
        }
    }
};

void AddSC_skip_StarterArea()
{
    new SPP_skip_deathknight_announce;
    new SPP_skip_deathknight;
    new spp_skip_goblin;
    new SPP_skip_goblin_announce;
    new SPP_skip_worgen_announce;
    new spp_skip_worgen;
    new SPP_skip_pandaren;
}