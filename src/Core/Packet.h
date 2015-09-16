//----------------------------------------------------------------------
// 
// Filename    : Packet.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __PACKET_H__
#define __PACKET_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

class Socket;
class Player;

//----------------------------------------------------------------------
// Packet ID Type
//----------------------------------------------------------------------
typedef ushort PacketID_t;
const uint szPacketID = sizeof(PacketID_t);

//----------------------------------------------------------------------
// Packet Size Type
//----------------------------------------------------------------------
typedef uint PacketSize_t;
const uint szPacketSize = sizeof(PacketSize_t);

//----------------------------------------------------------------------
// Packet Header Size
//----------------------------------------------------------------------
const uint szPacketHeader = szPacketID + szPacketSize;


//----------------------------------------------------------------------
//
// class Packet;
//
// ��Ŷ ����Ÿ�� ��Ÿ���� �������̽� Ŭ�����̴�.
//
// read()�� write()�� ���Ǳ��� ���캸��. �����Է½�Ʈ���� ������½�Ʈ����
// ��� ��Ŷ�� ��� �а� �� �������� �� �� ����. ����, ��Ŷ �ڽ��� ��
// ��Ʈ���� ��� �а� �� �������� �˰� �־�� �Ѵ�.
//
//----------------------------------------------------------------------

class Packet {
public:
    //----------------------------------------------------------------------
    //
    // Packet ID
    //
    // prefix�� �켱������ G > L > C �̴�. (GL/LG, GC/CG, LC/CL)
    // � ��⿡�� � �͵��� �����ؾ� �ϴ��� ���Ǳ��� �����ؾ� �Ѵ�.
    // ���� LC�� �α��μ����� Ŭ���̾�Ʈ ��� �����ؾ� �ϴ� ����̴�.
    //
    //----------------------------------------------------------------------
    enum {
        PACKET_CG_ADD_SMS_ADDRESS = 0,
        PACKET_CG_ABSORB_SOUL,
        PACKET_CG_ACCEPT_UNION,
        PACKET_CG_ADD_GEAR_TO_MOUSE,
        PACKET_CG_ADD_INVENTORY_TO_MOUSE,
        PACKET_CG_ADD_ITEM_TO_CODE_SHEET,
        PACKET_CG_ADD_ITEM_TO_ITEM,
        PACKET_CG_ADD_MOUSE_TO_GEAR,
        PACKET_CG_ADD_MOUSE_TO_INVENTORY,
        PACKET_CG_ADD_MOUSE_TO_QUICKSLOT,
        PACKET_CG_ADD_MOUSE_TO_ZONE,
        PACKET_CG_ADD_QUICKSLOT_TO_MOUSE,
        PACKET_CG_ADD_ZONE_TO_INVENTORY,
        PACKET_CG_ADD_ZONE_TO_MOUSE,
        PACKET_CG_APPOINT_SUBMASTER,
        PACKET_CG_ATTACK,
        PACKET_CG_AUTH_KEY,
        PACKET_CG_BLOOD_DRAIN,
        PACKET_CG_BUY_STORE_ITEM,
        PACKET_CG_CASTING_SKILL,
        PACKET_CG_COMMAND_MONSTER,
        PACKET_CG_CONNECT,
        PACKET_CG_CRASH_REPORT,
        PACKET_CG_DELETE_SMS_ADDRESS,
        PACKET_CG_DENY_UNION,
        PACKET_CG_DEPOSIT_PET,
        PACKET_CG_DIAL_UP,
        PACKET_CG_DISPLAY_ITEM,
        PACKET_CG_DISSECTION_CORPSE,
        PACKET_CG_DONATION_MONEY,
        PACKET_CG_DOWN_SKILL,
        PACKET_CG_DROP_MONEY,
        PACKET_CG_EXPEL_GUILD,
        PACKET_CG_EXPEL_GUILD_MEMBER,
        PACKET_CG_FAIL_QUEST,
        PACKET_CG_GET_EVENT_ITEM,
        PACKET_CG_GET_OFF_MOTORCYCLE,
        PACKET_CG_GLOBAL_CHAT,
        PACKET_CG_GQUEST_ACCEPT,
        PACKET_CG_GQUEST_CANCEL,
        PACKET_CG_GUILD_CHAT,
        PACKET_CG_JOIN_GUILD,
        PACKET_CG_LEARN_SKILL,
        PACKET_CG_LOGOUT,
        PACKET_CG_LOTTERY_SELECT,
        PACKET_CG_MAKE_ITEM,
        PACKET_CG_MIX_ITEM,
        PACKET_CG_MODIFY_GUILD_INTRO,
        PACKET_CG_MODIFY_GUILD_MEMBER,
        PACKET_CG_MODIFY_GUILDMEMBER_INTRO,
        PACKET_CG_MODIFY_NICKNAME,
        PACKET_CG_MODIFY_TAX_RATIO,
        PACKET_CG_MOUSE_TO_STASH,
        PACKET_CG_MOVE,
        PACKET_CG_NPC_ASK_ANSWER,
        PACKET_CG_NPC_TALK,
        PACKET_CG_PARTY_INVITE,
        PACKET_CG_PARTY_LEAVE,
        PACKET_CG_PARTY_POSITION,
        PACKET_CG_PARTY_SAY,
        PACKET_CG_PET_GAMBLE,
        PACKET_CG_PHONE_DISCONNECT,
        PACKET_CG_PHONE_SAY,
        PACKET_CG_PICKUP_MONEY,
        PACKET_CG_PORT_CHECK,
        PACKET_CG_QUIT_GUILD,
        PACKET_CG_QUIT_UNION,
        PACKET_CG_QUIT_UNION_ACCEPT,
        PACKET_CG_QUIT_UNION_DENY,
        PACKET_CG_RANGER_SAY,
        PACKET_CG_READY,
        PACKET_CG_REGIST_GUILD,
        PACKET_CG_RELIC_TO_OBJECT,
        PACKET_CG_RELOAD_FROM_INVENTORY,
        PACKET_CG_RELOAD_FROM_QUICKSLOT,
        PACKET_CG_REQUEST_GUILD_LIST,
        PACKET_CG_REQUEST_GUILD_MEMBER_LIST,
        PACKET_CG_REQUEST_INFO,
        PACKET_CG_REQUEST_IP,
        PACKET_CG_REQUEST_NEWBIE_ITEM,
        PACKET_CG_REQUEST_POWER_POINT,
        PACKET_CG_REQUEST_REPAIR,
        PACKET_CG_REQUEST_STORE_INFO,
        PACKET_CG_REQUEST_UNION,
        PACKET_CG_REQUEST_UNION_INFO,
        PACKET_CG_RESURRECT,
        PACKET_CG_RIDE_MOTORCYCLE,
        PACKET_CG_SAY,
        PACKET_CG_SELECT_BLOOD_BIBLE,
        PACKET_CG_SELECT_GUILD,
        PACKET_CG_SELECT_GUILD_MEMBER,
        PACKET_CG_SELECT_NICKNAME,
        PACKET_CG_SELECT_PORTAL,
        PACKET_CG_SELECT_QUEST,
        PACKET_CG_SELECT_RANK_BONUS,
        PACKET_CG_SELECT_REGEN_ZONE,
        PACKET_CG_SELECT_TILE_EFFECT,
        PACKET_CG_SELECT_WAYPOINT,
        PACKET_CG_SET_SLAYER_HOT_KEY,
        PACKET_CG_SET_VAMPIRE_HOT_KEY,
        PACKET_CG_SHOP_REQUEST_BUY,
        PACKET_CG_SHOP_REQUEST_LIST,
        PACKET_CG_SHOP_REQUEST_SELL,
        PACKET_CG_SILVER_COATING,
        PACKET_CG_SKILL_TO_INVENTORY,
        PACKET_CG_SKILL_TO_NAMED,
        PACKET_CG_SKILL_TO_OBJECT,
        PACKET_CG_SKILL_TO_SELF,
        PACKET_CG_SKILL_TO_TILE,
        PACKET_CG_SMS_ADDRESS_LIST,
        PACKET_CG_SMS_SEND,
        PACKET_CG_STASH_DEPOSIT,
        PACKET_CG_STASH_LIST,
        PACKET_CG_STASH_REQUEST_BUY,
        PACKET_CG_STASH_TO_MOUSE,
        PACKET_CG_STASH_WITHDRAW,
        PACKET_CG_STORE_CLOSE,
        PACKET_CG_STORE_OPEN,
        PACKET_CG_STORE_SIGN,
        PACKET_CG_SUBMIT_SCORE,
        PACKET_CG_TAKE_OUT_GOOD,
        PACKET_CG_TAME_MONSTER,
        PACKET_CG_THROW_BOMB,
        PACKET_CG_THROW_ITEM,
        PACKET_CG_TRADE_ADD_ITEM,
        PACKET_CG_TRADE_FINISH,
        PACKET_CG_TRADE_MONEY,
        PACKET_CG_TRADE_PREPARE,
        PACKET_CG_TRADE_REMOVE_ITEM,
        PACKET_CG_TRY_JOIN_GUILD,
        PACKET_CG_TYPE_STRING_LIST,
        PACKET_CG_UNBURROW,
        PACKET_CG_UNDISPLAY_ITEM,
        PACKET_CG_UNTRANSFORM,
        PACKET_CG_USE_BONUS_POINT,
        PACKET_CG_USE_ITEM_FROM_GEAR,
        PACKET_CG_USE_ITEM_FROM_GQUEST_INVENTORY,
        PACKET_CG_USE_ITEM_FROM_INVENTORY,
        PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY,
        PACKET_CG_USE_POTION_FROM_INVENTORY,
        PACKET_CG_USE_POTION_FROM_QUICKSLOT,
        PACKET_CG_USE_POWER_POINT,
        PACKET_CG_VERIFY_TIME,
        PACKET_CG_VISIBLE,
        PACKET_CG_WHISPER,
        PACKET_CG_WITHDRAW_PET,
        PACKET_CG_WITHDRAW_TAX,
        PACKET_CL_CHANGE_SERVER,
        PACKET_CL_CREATE_PC,
        PACKET_CL_DELETE_PC,
        PACKET_CL_GET_PC_LIST,
        PACKET_CL_GET_SERVER_LIST,
        PACKET_CL_GET_WORLD_LIST,
        PACKET_CL_LOGIN,
        PACKET_CL_LOGOUT,
        PACKET_CL_QUERY_CHARACTER_NAME,
        PACKET_CL_QUERY_PLAYER_ID,
        PACKET_CL_RECONNECT_LOGIN,
        PACKET_CL_REGISTER_PLAYER,
        PACKET_CL_SELECT_PC,
        PACKET_CL_SELECT_SERVER,
        PACKET_CL_SELECT_WORLD,
        PACKET_CL_VERSION_CHECK,
        PACKET_COMMON_BILLING,
        PACKET_CR_CONNECT,
        PACKET_CR_DISCONNECT,
        PACKET_CR_REQUEST,
        PACKET_CR_WHISPER,
        PACKET_CU_BEGIN_UPDATE,
        PACKET_CU_END_UPDATE,
        PACKET_CU_REQUEST,
        PACKET_CU_REQUEST_LOGIN_MODE,
        PACKET_GC_ACTIVE_GUILD_LIST,
        PACKET_GC_ADD_BAT,
        PACKET_GC_ADD_BURROWING_CREATURE,
        PACKET_GC_ADD_EFFECT,
        PACKET_GC_ADD_EFFECT_TO_TILE,
        PACKET_GC_ADD_GEAR_TO_INVENTORY,
        PACKET_GC_ADD_GEAR_TO_ZONE,
        PACKET_GC_ADD_HELICOPTER,
        PACKET_GC_ADD_INJURIOUS_CREATURE,
        PACKET_GC_ADD_INSTALLED_MINE_TO_ZONE,
        PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY,
        PACKET_GC_ADD_MONSTER,
        PACKET_GC_ADD_MONSTER_CORPSE,
        PACKET_GC_ADD_MONSTER_FROM_BURROWING,
        PACKET_GC_ADD_MONSTER_FROM_TRANSFORMATION,
        PACKET_GC_ADD_NEW_ITEM_TO_ZONE,
        PACKET_GC_ADD_NICKNAME,
        PACKET_GC_ADD_NPC,
        PACKET_GC_ADD_OUSTERS,
        PACKET_GC_ADD_OUSTERS_CORPSE,
        PACKET_GC_ADD_SLAYER,
        PACKET_GC_ADD_SLAYER_CORPSE,
        PACKET_GC_ADD_STORE_ITEM,
        PACKET_GC_ADD_VAMPIRE,
        PACKET_GC_ADD_VAMPIRE_CORPSE,
        PACKET_GC_ADD_VAMPIRE_FROM_BURROWING,
        PACKET_GC_ADD_VAMPIRE_FROM_TRANSFORMATION,
        PACKET_GC_ADD_VAMPIRE_PORTAL,
        PACKET_GC_ADD_WOLF,
        PACKET_GC_ADDRESS_LIST_VERIFY,
        PACKET_GC_ATTACK,
        PACKET_GC_ATTACK_ARMS_OK_1,
        PACKET_GC_ATTACK_ARMS_OK_2,
        PACKET_GC_ATTACK_ARMS_OK_3,
        PACKET_GC_ATTACK_ARMS_OK_4,
        PACKET_GC_ATTACK_ARMS_OK_5,
        PACKET_GC_ATTACK_MELEE_OK_1,
        PACKET_GC_ATTACK_MELEE_OK_2,
        PACKET_GC_ATTACK_MELEE_OK_3,
        PACKET_GC_AUTH_KEY,
        PACKET_GC_BLOOD_BIBLE_LIST,
        PACKET_GC_BLOOD_BIBLE_SIGN_INFO,
        PACKET_GC_BLOOD_BIBLE_STATUS,
        PACKET_GC_BLOOD_DRAIN_OK_1,
        PACKET_GC_BLOOD_DRAIN_OK_2,
        PACKET_GC_BLOOD_DRAIN_OK_3,
        PACKET_GC_CANNOT_ADD,
        PACKET_GC_CANNOT_USE,
        PACKET_GC_CASTING_SKILL,
        PACKET_GC_CHANGE_DARK_LIGHT,
        PACKET_GC_CHANGE_SHAPE,
        PACKET_GC_CHANGE_WEATHER,
        PACKET_GC_CREATE_ITEM,
        PACKET_GC_CREATURE_DIED,
        PACKET_GC_CROSS_COUNTER_OK_1,
        PACKET_GC_CROSS_COUNTER_OK_2,
        PACKET_GC_CROSS_COUNTER_OK_3,
        PACKET_GC_DELETE_AND_PICKUP_OK,
        PACKET_GC_DELETE_EFFECT_FROM_TILE,
        PACKET_GC_DELETE_INVENTORY_ITEM,
        PACKET_GC_DELETE_OBJECT,
        PACKET_GC_DISCONNECT,
        PACKET_GC_DOWN_SKILL_FAILED,
        PACKET_GC_DOWN_SKILL_OK,
        PACKET_GC_DROP_ITEM_TO_ZONE,
        PACKET_GC_ENTER_VAMPIRE_PORTAL,
        PACKET_GC_EXECUTE_ELEMENT,
        PACKET_GC_FAKE_MOVE,
        PACKET_GC_FAST_MOVE,
        PACKET_GC_FLAG_WAR_STATUS,
        PACKET_GC_GET_DAMAGE,
        PACKET_GC_GET_OFF_MOTORCYCLE,
        PACKET_GC_GET_OFF_MOTORCYCLE_FAILED,
        PACKET_GC_GET_OFF_MOTORCYCLE_OK,
        PACKET_GC_GLOBAL_CHAT,
        PACKET_GC_GOODS_LIST,
        PACKET_GC_GQUEST_INVENTORY,
        PACKET_GC_GQUEST_STATUS_INFO,
        PACKET_GC_GQUEST_STATUS_MODIFY,
        PACKET_GC_GUILD_CHAT,
        PACKET_GC_GUILD_MEMBER_LIST,
        PACKET_GC_GUILD_RESPONSE,
        PACKET_GC_HOLY_LAND_BONUS_INFO,
        PACKET_GC_HP_RECOVERY_END_TO_OTHERS,
        PACKET_GC_HP_RECOVERY_END_TO_SELF,
        PACKET_GC_HP_RECOVERY_START_TO_OTHERS,
        PACKET_GC_HP_RECOVERY_START_TO_SELF,
        PACKET_GC_KICK_MESSAGE,
        PACKET_GC_KNOCK_BACK,
        PACKET_GC_KNOCKS_TARGET_BACK_OK_1,
        PACKET_GC_KNOCKS_TARGET_BACK_OK_2,
        PACKET_GC_KNOCKS_TARGET_BACK_OK_4,
        PACKET_GC_KNOCKS_TARGET_BACK_OK_5,
        PACKET_GC_LEARN_SKILL_FAILED,
        PACKET_GC_LEARN_SKILL_OK,
        PACKET_GC_LEARN_SKILL_READY,
        PACKET_GC_LIGHTNING,
        PACKET_GC_MAKE_ITEM_FAIL,
        PACKET_GC_MAKE_ITEM_OK,
        PACKET_GC_MINE_EXPLOSION_OK_1,
        PACKET_GC_MINE_EXPLOSION_OK_2,
        PACKET_GC_MINI_GAME_SCORES,
        PACKET_GC_MODIFY_GUILD_MEMBER_INFO,
        PACKET_GC_MODIFY_INFORMATION,
        PACKET_GC_MODIFY_MONEY,
        PACKET_GC_MODIFY_NICKNAME,
        PACKET_GC_MONSTER_KILL_QUEST_INFO,
        PACKET_GC_MORPH_1,
        PACKET_GC_MORPH_SLAYER_2,
        PACKET_GC_MORPH_VAMPIRE_2,
        PACKET_GC_MOVE,
        PACKET_GC_MOVE_ERROR,
        PACKET_GC_MOVE_OK,
        PACKET_GC_MP_RECOVERY_END,
        PACKET_GC_MP_RECOVERY_START,
        PACKET_GC_MY_STORE_INFO,
        PACKET_GC_NICKNAME_LIST,
        PACKET_GC_NICKNAME_VERIFY,
        PACKET_GC_NOTICE_EVENT,
        PACKET_GC_NOTIFY_WIN,
        PACKET_GC_NPC_ASK,
        PACKET_GC_NPC_ASK_VARIABLE,
        PACKET_GC_NPC_ASK_DYNAMIC,
        PACKET_GC_NPC_INFO,
        PACKET_GC_NPC_RESPONSE,
        PACKET_GC_NPC_SAY,
        PACKET_GC_NPC_SAY_DYNAMIC,
        PACKET_GC_OTHER_GUILD_NAME,
        PACKET_GC_OTHER_MODIFY_INFO,
        PACKET_GC_OTHER_STORE_INFO,
        PACKET_GC_PARTY_ERROR,
        PACKET_GC_PARTY_INVITE,
        PACKET_GC_PARTY_JOINED,
        PACKET_GC_PARTY_LEAVE,
        PACKET_GC_PARTY_POSITION,
        PACKET_GC_PARTY_SAY,
        PACKET_GC_PET_INFO,
        PACKET_GC_PET_STASH_LIST,
        PACKET_GC_PET_STASH_VERIFY,
        PACKET_GC_PET_USE_SKILL,
        PACKET_GC_PHONE_CONNECTED,
        PACKET_GC_PHONE_CONNECTION_FAILED,
        PACKET_GC_PHONE_DISCONNECTED,
        PACKET_GC_PHONE_SAY,
        PACKET_GC_QUEST_STATUS,
        PACKET_GC_RANK_BONUS_INFO,
        PACKET_GC_REAL_WEARING_INFO,
        PACKET_GC_RECONNECT,
        PACKET_GC_RECONNECT_LOGIN,
        PACKET_GC_REGEN_ZONE_STATUS,
        PACKET_GC_RELOAD_OK,
        PACKET_GC_REMOVE_CORPSE_HEAD,
        PACKET_GC_REMOVE_EFFECT,
        PACKET_GC_REMOVE_FROM_GEAR,
        PACKET_GC_REMOVE_INJURIOUS_CREATURE,
        PACKET_GC_REMOVE_STORE_ITEM,
        PACKET_GC_REQUEST_FAILED,
        PACKET_GC_REQUEST_POWER_POINT_RESULT,
        PACKET_GC_REQUESTED_IP,
        PACKET_GC_RIDE_MOTORCYCLE,
        PACKET_GC_RIDE_MOTORCYCLE_FAILED,
        PACKET_GC_RIDE_MOTORCYCLE_OK,
        PACKET_GC_RING,
        PACKET_GC_SAY,
        PACKET_GC_SEARCH_MOTORCYCLE_FAIL,
        PACKET_GC_SEARCH_MOTORCYCLE_OK,
        PACKET_GC_SELECT_QUEST_ID,
        PACKET_GC_SELECT_RANK_BONUS_FAILED,
        PACKET_GC_SELECT_RANK_BONUS_OK,
        PACKET_GC_SET_POSITION,
        PACKET_GC_SHOP_BOUGHT,
        PACKET_GC_SHOP_BUY_FAIL,
        PACKET_GC_SHOP_BUY_OK,
        PACKET_GC_SHOP_LIST,
        PACKET_GC_SHOP_LIST_MYSTERIOUS,
        PACKET_GC_SHOP_MARKET_CONDITION,
        PACKET_GC_SHOP_SELL_FAIL,
        PACKET_GC_SHOP_SELL_OK,
        PACKET_GC_SHOP_SOLD,
        PACKET_GC_SHOP_VERSION,
        PACKET_GC_SHOW_GUILD_INFO,
        PACKET_GC_SHOW_GUILD_JOIN,
        PACKET_GC_SHOW_GUILD_MEMBER_INFO,
        PACKET_GC_SHOW_GUILD_REGIST,
        PACKET_GC_SHOW_MESSAGE_BOX,
        PACKET_GC_SHOW_UNION_INFO,
        PACKET_GC_SHOW_WAIT_GUILD_INFO,
        PACKET_GC_SKILL_FAILED_1,
        PACKET_GC_SKILL_FAILED_2,
        PACKET_GC_SKILL_INFO,
        PACKET_GC_SKILL_TO_INVENTORY_OK_1,
        PACKET_GC_SKILL_TO_INVENTORY_OK_2,
        PACKET_GC_SKILL_TO_OBJECT_OK_1,
        PACKET_GC_SKILL_TO_OBJECT_OK_2,
        PACKET_GC_SKILL_TO_OBJECT_OK_3,
        PACKET_GC_SKILL_TO_OBJECT_OK_4,
        PACKET_GC_SKILL_TO_OBJECT_OK_5,
        PACKET_GC_SKILL_TO_OBJECT_OK_6,
        PACKET_GC_SKILL_TO_SELF_OK_1,
        PACKET_GC_SKILL_TO_SELF_OK_2,
        PACKET_GC_SKILL_TO_SELF_OK_3,
        PACKET_GC_SKILL_TO_TILE_OK_1,
        PACKET_GC_SKILL_TO_TILE_OK_2,
        PACKET_GC_SKILL_TO_TILE_OK_3,
        PACKET_GC_SKILL_TO_TILE_OK_4,
        PACKET_GC_SKILL_TO_TILE_OK_5,
        PACKET_GC_SKILL_TO_TILE_OK_6,
        PACKET_GC_SMS_ADDRESS_LIST,
        PACKET_GC_STASH_LIST,
        PACKET_GC_STASH_SELL,
        PACKET_GC_STATUS_CURRENT_HP,
        PACKET_GC_SUB_INVENTORY_INFO,
        PACKET_GC_SWEEPER_BONUS_INFO,
        PACKET_GC_SYSTEM_AVAILABILITIES,
        PACKET_GC_SYSTEM_MESSAGE,
        PACKET_GC_TAKE_OFF,
        PACKET_GC_TAKE_OUT_FAIL,
        PACKET_GC_TAKE_OUT_OK,
        PACKET_GC_TEACH_SKILL_INFO,
        PACKET_GC_THROW_BOMB_OK_1,
        PACKET_GC_THROW_BOMB_OK_2,
        PACKET_GC_THROW_BOMB_OK_3,
        PACKET_GC_THROW_ITEM_OK_1,
        PACKET_GC_THROW_ITEM_OK_2,
        PACKET_GC_THROW_ITEM_OK_3,
        PACKET_GC_TIME_LIMIT_ITEM_INFO,
        PACKET_GC_TRADE_ADD_ITEM,
        PACKET_GC_TRADE_ERROR,
        PACKET_GC_TRADE_FINISH,
        PACKET_GC_TRADE_MONEY,
        PACKET_GC_TRADE_PREPARE,
        PACKET_GC_TRADE_REMOVE_ITEM,
        PACKET_GC_TRADE_VERIFY,
        PACKET_GC_UNBURROW_FAIL,
        PACKET_GC_UNBURROW_OK,
        PACKET_GC_UNION_OFFER_LIST,
        PACKET_GC_UNTRANSFORM_FAIL,
        PACKET_GC_UNTRANSFORM_OK,
        PACKET_GC_UPDATE_INFO,
        PACKET_GC_USE_BONUS_POINT_FAIL,
        PACKET_GC_USE_BONUS_POINT_OK,
        PACKET_GC_USE_OK,
        PACKET_GC_USE_POWER_POINT_RESULT,
        PACKET_GC_VISIBLE_FAIL,
        PACKET_GC_VISIBLE_OK,
        PACKET_GC_WAIT_GUILD_LIST,
        PACKET_GC_WAR_LIST,
        PACKET_GC_WAR_SCHEDULE_LIST,
        PACKET_GC_WHISPER,
        PACKET_GC_WHISPER_FAILED,
        PACKET_GG_COMMAND,
        PACKET_GG_GUILD_CHAT,
        PACKET_GG_SERVER_CHAT,
        PACKET_GL_INCOMING_CONNECTION,
        PACKET_GL_INCOMING_CONNECTION_ERROR,
        PACKET_GL_INCOMING_CONNECTION_OK,
        PACKET_GL_KICK_VERIFY,
        PACKET_GM_SERVER_INFO,
        PACKET_GS_ADD_GUILD,
        PACKET_GS_ADD_GUILD_MEMBER,
        PACKET_GS_EXPEL_GUILD_MEMBER,
        PACKET_GS_GUILD_ACTION,
        PACKET_GS_GUILDMEMBER_LOGON,
        PACKET_GS_MODIFY_GUILD_INTRO,
        PACKET_GS_MODIFY_GUILD_MEMBER,
        PACKET_GS_QUIT_GUILD,
        PACKET_GS_REQUEST_GUILD_INFO,
        PACKET_GTO_ACKNOWLEDGEMENT,
        PACKET_LC_CREATE_PC_ERROR,
        PACKET_LC_CREATE_PC_OK,
        PACKET_LC_DELETE_PC_ERROR,
        PACKET_LC_DELETE_PC_OK,
        PACKET_LC_LOGIN_ERROR,
        PACKET_LC_LOGIN_OK,
        PACKET_LC_PC_LIST,
        PACKET_LC_PORT_CHECK,
        PACKET_LC_QUERY_RESULT_CHARACTER_NAME,
        PACKET_LC_QUERY_RESULT_PLAYER_ID,
        PACKET_LC_RECONNECT,
        PACKET_LC_REGISTER_PLAYER_ERROR,
        PACKET_LC_REGISTER_PLAYER_OK,
        PACKET_LC_SELECT_PC_ERROR,
        PACKET_LC_SERVER_LIST,
        PACKET_LC_VERSION_CHECK_ERROR,
        PACKET_LC_VERSION_CHECK_OK,
        PACKET_LC_WORLD_LIST,
        PACKET_LG_INCOMING_CONNECTION,
        PACKET_LG_INCOMING_CONNECTION_ERROR,
        PACKET_LG_INCOMING_CONNECTION_OK,
        PACKET_LG_KICK_CHARACTER,
        PACKET_RC_CHARACTER_INFO,
        PACKET_RC_CONNECT_VERIFY,
        PACKET_RC_POSITION_INFO,
        PACKET_RC_REQUESTED_FILE,
        PACKET_RC_REQUEST_VERIFY,
        PACKET_RC_SAY,
        PACKET_RC_STATUS_HP,
        PACKET_SG_ADD_GUILD_MEMBER_OK,
        PACKET_SG_ADD_GUILD_OK,
        PACKET_SG_DELETE_GUILD_OK,
        PACKET_SG_EXPEL_GUILD_MEMBER_OK,
        PACKET_SG_GUILD_INFO,
        PACKET_SG_GUILD_RESPONSE,
        PACKET_SG_GUILDMEMBER_LOGON_OK,
        PACKET_SG_MODIFY_GUILD_INTRO_OK,
        PACKET_SG_MODIFY_GUILD_MEMBER_OK,
        PACKET_SG_MODIFY_GUILD_OK,
        PACKET_SG_QUIT_GUILD_OK,
        PACKET_UC_REQUEST_LOGIN_MODE,
        PACKET_UC_UPDATE,
        PACKET_UC_UPDATE_LIST,
        PACKET_CL_AGREEMENT,
        PACKET_MAX
    };

    virtual ~Packet() {}

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    virtual void read(SocketInputStream & iStream) throw(ProtocolException, Error) = 0;

    // �������κ��� ���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    virtual void read(Socket* pSocket) throw(ProtocolException, Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    virtual void write(SocketOutputStream & oStream) const throw(ProtocolException, Error) = 0;

    // �������� ���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    virtual void write(Socket* pSocket) const throw(ProtocolException, Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // ��� ��Ʈ���� ��Ŷ�� ����� �ٵ� ��� ����.
    void writeHeaderNBody(SocketOutputStream& oStream) const {
        oStream.write(getPacketID());
        oStream.write(getPacketSize());
        if (getPacketSize() != 0)
            write(oStream);
    }

    // execute packet's handler
    virtual void execute(Player* pPlayer) throw(ProtocolException, Error) = 0;

    virtual PacketID_t getPacketID() const throw() = 0;
    virtual PacketSize_t getPacketSize() const throw() = 0;

    #if !defined(__GAME_CLIENT__) || defined(__DEBUG_OUTPUT__)
        virtual string getPacketName() const throw() = 0;

        virtual string toString() const throw() = 0;
    #endif
};
#endif