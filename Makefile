CL_NAME	=	uchat
SV_NAME = 	uchat_server

#CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g
CFLG	=	-std=c11 -Wall -Wextra #-g -fsanitize=address
INCD = inc


CL_SRCD	=	client/src
SV_SRCD =	server/src
#DB_SRCD =	datab/src
CL_INCD	=	client/inc
# #SV_INCD =	server/inc
#DB_INCD =	datab/inc
CL_OBJD	=	client/obj
SV_OBJD =	server/obj
#DB_OBJD =	datab/obj
CL_GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`
#SQL_FLAGS = -lsqlite3
SANITAIZER_FLAGS =  -fsanitize=address
CL_THREADS_LINKER = -pthread -lpthread

CJSON		= cJSON.a
CJSON_INCS 	= cJSON.h
CJSON_INC	= cjson/inc/cJSON.h

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/inc

#DB_MXD	=	datab
#DB_MXA:=	$(DB_MXD)/dich_db -lsqlite3 $(DB_MXA) #-I$(DB_MXI)
#DB_MXI:=	$(DB_MXD)/$(INCD)

INC_AL		=	server.h \
				database.h \
				sqlite3.h \

CL_INCS		=	 client.h

#SV_INC		=	server.h

INCS 	=	$(addprefix $(INCD)/, $(INC_AL))
CL_INCS	=	$(addprefix $(CL_INCD)/, $(CL_INC))

CL_SRC		=	add_to_arr_new_contact.c \
				arr_size.c \
				chat_signals.c \
				hash.c \
				jsn_get_chat_with_user.c \
				jsn_get_message.c \
				jsn_log_in.c \
				jsn_profile.c \
				jsn_send_message.c \
				jsn_sign_in.c \
				login_signals.c \
				mx_clear_container.c \
				mx_interface.c \
				mx_print_strarr.c \
				mx_strjoin.c \
				mx_strnew.c \
				parse_arr.c \
				print_last_message.c \
				print_new_message.c \
				printer.c \
				printer_message.c \
				printer_reply_message.c \
				profile_signal.c \
				signup_signals.c \
				strjoin_f_and_l.c \
				time_doing.c \
				jsn_change_pasw.c \
				uchat.c

				
SV_SRC		=	add_private_message_to_db.c \
				by_phone_number_or_login.c \
				init_error_struct.c \
				chat_with_reply_to_jsn.c \
				chat_with_req_to_reply.c \
				fill_table_friends.c \
				get_chat_with_reply.c \
				get_info_from_friends_table.c \
				get_last_chat.c \
				insert_into_table_friends.c \
				jsn_to_chat_with_req.c \
				make_sql_get_last_messages.c \
				no_users.c \
				proverka_existense_id.c \
				proverka_tablic_friends.c \
				table_chat_exists.c \
				table_exists.c \
				check_user.c \
				delete_error.c \
				error_json.c \
				incorrect_key_type.c \
				failed_to_parse_json.c \
				failed_to_get_key_value.c \
				failed_to_open_db.c \
				failed_to_exec.c \
				no_table.c \
				jsn_to_registration_req.c \
				create_table_chats_with_friends.c \
				checking_matches_in_table_users.c \
				registration_reply_to_jsn.c \
				jsn_to_log_in_req.c \
				log_in_req_to_reply.c \
				log_in_reply_to_jsn.c \
				jsn_to_find_user_req.c \
				find_user_req_to_reply.c \
				find_user_reply_to_jsn.c \
				jsn_to_pr_message_req.c \
				private_message_req_to_reply.c \
				get_user_details.c \
				sozdanie_tablici.c \
				zapolnenie_tablici.c \
				private_mess_reply_to_jsn.c \
				get_reply_from_db.c \
				get_log_in_reply.c \
				get_registration_reply.c \
				get_find_user_reply.c \
				get_pr_message_reply.c \
				open_db.c \
				sql_make_simple_select_in.c \
				sqlite3_better_exec.c \
				find_user_by_credentials_and_fill_log_in_reply.c \
				get_found_user_info.c \
				inversion.c \
				get_value.c \
				is_empty_table.c \
				proverka_tablic.c \
				main_server.c \
				mx_daemon.c \
				procces.c \
				sqlite3.c \
				insert_curr_client.c \
				print_error.c \
				select_client_socket.c \
				update_uid.c \
				delete_client_from_db.c \
				change_passwd_reply_to_jsn.c \
				change_passwd_req_to_reply.c \
				get_change_passw_reply.c \
				jsn_to_change_passw_req.c \
				invalid_credentials.c \
				try_to_update_passwd.c
				
CL_SRCS	=	$(addprefix $(CL_SRCD)/, $(CL_SRC))
SV_SRCS =	$(addprefix $(SV_SRCD)/, $(SV_SRC))
CL_OBJS	=	$(addprefix $(CL_OBJD)/, $(CL_SRC:%.c=%.o))
SV_OBJS	=	$(addprefix $(SV_OBJD)/, $(SV_SRC:%.c=%.o))

all: install

$(FILE:a/%=%)

install: cjson_install lib_install install_server install_client

##install_db:
	#@make -sC $(DB_MXD)

cjson_install:
	@cp $(CJSON_INC) .
	@make -C cjson install
	@cp cjson/cJSON.a .

lib_install:
	# @cp $(LMXI) .
	@make -sC $(LMXD)
	@cp cjson/cJSON.a .
	
install_client: $(CL_NAME)

$(CL_NAME): $(CL_OBJS)
	@clang $(CFLG) $(CL_OBJS) $(CL_GTK_FLAGS) -L/usr/local/opt/openssl/lib/ -lssl -lcrypto -lmx -rdynamic -o $@ $(LIBS) $(CJSON)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(CL_OBJD)/%.o: $(CL_SRCD)/%.c $(CL_INCS)
	@clang $(CFLG) -c -I/usr/local/opt/openssl/include/ $< $(CL_GTK_SORT_FLAGS) -o $@ -I$(CL_INCD) 
	@printf "\r\33[2K$(CL_NAME) \033[33;1mcompile \033[0m$(<:$(CL_SRCD)/%.c=%) "

$(CL_OBJS): | $(CL_OBJD)

$(CL_OBJD):
	@mkdir -p $@

install_server: $(SV_NAME)

$(SV_NAME): $(SV_OBJS)
	@clang $(CFLG) $(SV_OBJS) -L$(LMXD) -lmx -o $@ $(CJSON) 
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(SV_OBJD)/%.o: $(SV_SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI) 
	@printf "\r\33[2K$(SV_NAME) \033[33;1mcompile \033[0m$(<:$(SV_SRCD)/%.c=%) "

$(SV_OBJS): | $(SV_OBJD)

$(SV_OBJD):
	@mkdir -p $@

$(DB_MXA):
	#@make -sC $(DB_MXD)

clean:
	@make -sC $(LMXD) $@
	@make -C cjson uninstall
	#@make -sC $(DB_MXD) $@
	@rm -rf $(CL_OBJD)
	@rm -rf $(SV_OBJD)
	#@rm -rf $(DB_MXD)/$(DB_MXA)
	@printf "$(CL_OBJD)\t   \033[31;1mdeleted\033[0m\n"
	@printf "$(SV_OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(CL_NAME)
	#@make -sC $(DB_MXD) $@
	@rm -rf $(SV_NAME)
	@printf "$(CL_NAME) \033[31;1muninstalled\033[0m\n"
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

uninstall_server:
	#@make -sC $(DB_MXD) uninstall
	@rm -rf $(SV_NAME)
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

reinstall_server : uninstall_server install_server
