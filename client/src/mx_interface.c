#include <client.h>

/* создание окна в этот раз мы вынесли в отдельную функцию */
static GtkWidget* create_window (void) {
    /* это виджет окна */
    
    /* это тот волшебный объект, который сделает за нас окошко */
    GtkBuilder *builder;
    /* сюда будем складывать ошибки */
    GError* error = NULL;
    GdkScreen *display = gdk_screen_get_default();
    cleint_data.gui->css_provider = gtk_css_provider_new();
    /* тут загружаем файл с интерфейсом */
    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, "glade/okno_chata6.glade", &error)) {
          /* загрузить файл не удалось */
            g_critical ("Не могу загрузить файл: %s", error->message);
            g_error_free (error);
    }
    /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));;
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals (builder, NULL);
    /* получаем виджет окна, чтобы его показать */
    g_object_ref(builder);
    cleint_data.gui->stack = GTK_STACK(gtk_builder_get_object(builder, "slider1"));
    cleint_data.gui->stack_chat = GTK_STACK(gtk_builder_get_object(builder, "slider_chat"));
    cleint_data.gui->settings_fix = GTK_STACK(gtk_builder_get_object(builder, "settings_slider"));
    cleint_data.gui->login_child = GTK_WIDGET(gtk_builder_get_object(builder, "login"));
    cleint_data.gui->sing_up_child = GTK_WIDGET(gtk_builder_get_object(builder, "sign_up"));
    cleint_data.gui->chat_child = GTK_WIDGET(gtk_builder_get_object(builder, "chat"));
    cleint_data.gui->chat_child0 = GTK_WIDGET(gtk_builder_get_object(builder, "chat0"));
    cleint_data.gui->user_and_friends_child = GTK_WIDGET(gtk_builder_get_object(builder, "user_and_friends_profile"));
    cleint_data.gui->err_login = GTK_WIDGET(gtk_builder_get_object(builder, "error_login_text"));
    cleint_data.gui->err_singup = GTK_WIDGET(gtk_builder_get_object(builder, "error_sign_up_text"));
    cleint_data.gui->entr_message = GTK_WIDGET(gtk_builder_get_object(builder, "enter_message"));
    cleint_data.gui->entr_search = GTK_WIDGET(gtk_builder_get_object(builder, "search_user_and_friends"));
    cleint_data.gui->label_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "nickname"));
    cleint_data.gui->label_id = GTK_WIDGET(gtk_builder_get_object(builder, "id"));
    cleint_data.gui->label_email = GTK_WIDGET(gtk_builder_get_object(builder, "email"));
    cleint_data.gui->label_number = GTK_WIDGET(gtk_builder_get_object(builder, "number"));
    cleint_data.gui->label_not_found = GTK_WIDGET(gtk_builder_get_object(builder, "not_found"));
    cleint_data.gui->label_chat1 = GTK_WIDGET(gtk_builder_get_object(builder, "err"));
    cleint_data.gui->label_chat2 = GTK_WIDGET(gtk_builder_get_object(builder, "err_chat"));
    cleint_data.gui->list_message = GTK_WIDGET(gtk_builder_get_object(builder, "list_message"));
    cleint_data.gui->list_chat = GTK_WIDGET(gtk_builder_get_object(builder, "users_list"));
    cleint_data.gui->swindow_chat = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder, "s_w_list_message"));
    cleint_data.gui->chang_pass = GTK_WIDGET(gtk_builder_get_object(builder, "Changing_password"));
    cleint_data.gui->settings = GTK_WIDGET(gtk_builder_get_object(builder, "theme"));
    cleint_data.gui->fix_set = GTK_WIDGET(gtk_builder_get_object(builder, "settings"));
    //g_object_unref(builder);
    if (!window) {
        g_critical ("Ошибка при получении виджета окна");
    }

    gtk_css_provider_load_from_path(cleint_data.gui->css_provider, "theme1.css", NULL);
    gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(cleint_data.gui->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref (builder);
    return window;
}

/* это главная функция нашего приложения, которая будет выполнена первой */
int mx_interface(int argc, char **argv, int sockfd) {

    cleint_data.soketfd = sockfd;
    //t_struct *cleint_data = (t_struct *)malloc(sizeof(t_struct));
    cleint_data.chat = (t_chat *)malloc(sizeof(t_chat));
    cleint_data.new_message = (t_send_jsn *)malloc(sizeof(t_send_jsn));
    cleint_data.new_message->date = NULL;
    cleint_data.new_message->new_message = NULL;
    cleint_data.new_message->receiver_id = NULL;
    cleint_data.new_message->sender_email = NULL;
    cleint_data.new_message->sender_f_name = NULL;
    cleint_data.new_message->sender_id = NULL;
    cleint_data.new_message->sender_l_name = NULL;
    cleint_data.new_message->sender_login = NULL;
    cleint_data.new_message->sender_ph_number = NULL;
    cleint_data.chat->arr_count = 0;
    //cleint_data.chat->dates = (char **)malloc(sizeof(char *) * 50);
    cleint_data.chat->friend_id = NULL;
    cleint_data.chat->friend_username = NULL;
    //cleint_data.chat->last_50_massege = (char **)malloc(sizeof(char *) * 50);
    cleint_data.chat->message = NULL;
    //cleint_data.chat->messages_senders = (char **)malloc(sizeof(char *) * 50);
    cleint_data.chat->time = NULL;
    cleint_data.chat->your_id = NULL;
    cleint_data.chat->your_username = NULL;
    cleint_data.profile = (t_profile *)malloc(sizeof(t_profile));
    cleint_data.profile->search_username = NULL;
    cleint_data.profile->search_user_id = NULL;
    cleint_data.profile->search_user_fn = NULL;
    cleint_data.profile->search_user_ln = NULL;
    cleint_data.profile->search_user_em = NULL;
    cleint_data.profile->search_user_num = NULL;
    cleint_data.profile->search_user_fl = NULL;
    cleint_data.chat->message = NULL;
    cleint_data.gui = (t_gui *)malloc(sizeof(t_gui));
    cleint_data.login = (t_login *)malloc(sizeof(t_login));
    cleint_data.login_jsn = (t_login_jsn *)malloc(sizeof(t_login_jsn));
    cleint_data.login->username = NULL;
    cleint_data.login->password = NULL;
    cleint_data.signup = (t_signup *)malloc(sizeof(t_signup));
    cleint_data.signup->confpass_sign = NULL;
    cleint_data.signup->email_sign = NULL;
    cleint_data.signup->firstname_sign = NULL;
    cleint_data.signup->lastname_sign = NULL;
    cleint_data.signup->passw_sign = NULL;
    cleint_data.signup->phonenum_sign = NULL;
    cleint_data.signup->username_sign = NULL;
    // cleint_data.login_jsn->userschat = (char **)malloc(sizeof(char *) * 50);
    // cleint_data.login_jsn->friends_f_name = (char **)malloc(sizeof(char *) * 50);
    // cleint_data.login_jsn->friends_l_name = (char **)malloc(sizeof(char *) * 50);
    // cleint_data.login_jsn->friends_id = (char **)malloc(sizeof(char *) * 50);
    // cleint_data.login_jsn->friends_ph_number = (char **)malloc(sizeof(char *) * 50);
    // cleint_data.login_jsn->friends_email = (char **)malloc(sizeof(char *) * 50);
    // for (int i = 0; i < 50; i++) {
    //     cleint_data.chat->dates[i] = NULL;
    //     cleint_data.chat->messages_senders[i] = NULL;
    //     cleint_data.chat->last_50_massege[i] = NULL;
    //     cleint_data.login_jsn->userschat[i] = NULL; 
    //     cleint_data.login_jsn->friends_f_name[i] = NULL;
    //     cleint_data.login_jsn->friends_l_name[i] = NULL;
    //     cleint_data.login_jsn->friends_id[i] = NULL;
    //     cleint_data.login_jsn->friends_ph_number[i] = NULL;
    //     cleint_data.login_jsn->friends_email[i] = NULL;
    // }
    /* виджет окна */
    GtkWidget *window;
    /* запускаем GTK+ */
    gtk_init (&argc, &argv);
    /* вызываем нашу функцию для создания окна */
    window = create_window ();
    gtk_widget_show (window);

    // int errthread = pthread_create(&x, NULL, (void *)jsn_get_message, NULL);
    // if (errthread != 0) {
    //     printf("\ncan't create thread :[%s]", strerror(errthread));
    // }
    g_thread_new("change_flag", (GThreadFunc)jsn_get_message, NULL);
    /* передаём управление GTK+ */
    gtk_main ();
    return 0;
}
