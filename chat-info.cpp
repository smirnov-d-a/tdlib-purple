#include "chat-info.h"
#include "config.h"

static char idKey[] = "id";

GList *getChatJoinInfo()
{
    struct proto_chat_entry *pce;
    pce = g_new0 (struct proto_chat_entry, 1);
    pce->label = "Chat ID:";
    pce->identifier = idKey;
    pce->required = FALSE;
    GList *info = g_list_append (NULL, pce);

    pce = g_new0 (struct proto_chat_entry, 1);
    pce->label = "Invite link:";
    pce->identifier = "link";
    pce->required = FALSE;
    info = g_list_append (info, pce);

    pce = g_new0 (struct proto_chat_entry, 1);
    pce->label = "Subject:";
    pce->identifier = "subject";
    pce->required = FALSE;
    info = g_list_append (info, pce);

    return info;
}

std::string getChatName(const td::td_api::chat &chat)
{
    return "chat" + std::to_string(chat.id_);
}

GHashTable *getChatComponents(const td::td_api::chat &chat)
{
    char name[32];
    snprintf(name, sizeof(name)-1, "chat%lld", (long long)chat.id_);
    name[sizeof(name)-1] = '\0';

    GHashTable *table = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, g_free);
    g_hash_table_insert(table, idKey, g_strdup(name));
    return table;
}