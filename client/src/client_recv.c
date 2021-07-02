#include "client.h"

void *mx_client_recv(void *data) {
    int n = 0;
    t_s_glade *gui = *(t_s_glade **)data;
    char *answer = NULL;
    json_object *jobj = NULL;

    while (true) {
        bzero(gui->buffer, MX_MAX_BYTES);
        n = recv(gui->sockfd, gui->buffer, MX_MAX_BYTES, 0);
        if (n <= 0) {
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_reconecting, gui, 0);
            sleep(5);
            exit(0);
        }
        jobj = json_tokener_parse(gui->buffer);
        gui->recv_data = strdup(gui->buffer);
        answer = (char *)json_object_get_string(json_object_object_get(jobj, "Answer"));
        first_handle(answer, gui, jobj);
        second_handle(answer, gui);
        third_handle(answer, gui);
        fourth_handle(answer, gui);
    }
    return NULL;
}