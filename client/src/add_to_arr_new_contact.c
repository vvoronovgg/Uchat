#include "client.h"

void add_to_arr_new_contact (void) {
    cleint_data.profile->count_arr = arr_size(cleint_data.login_jsn->userschat);
    cleint_data.login_jsn->userschat[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_username);
    cleint_data.login_jsn->friends_f_name[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_user_fn);
    cleint_data.login_jsn->friends_l_name[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_user_ln);
    cleint_data.login_jsn->friends_id[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_user_id);
    cleint_data.login_jsn->friends_ph_number[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_user_num);
    cleint_data.login_jsn->friends_email[cleint_data.profile->count_arr] = strdup(cleint_data.profile->search_user_em);
    cleint_data.profile->count_arr++;
}
