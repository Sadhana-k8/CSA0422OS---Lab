#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

// Message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {

    key_t key = ftok("msgfile", 65);

    int msgid = msgget(key, 0666 | IPC_CREAT);

    pid_t pid = fork();

    if (pid > 0) {
        //---------------- Parent : Send message ----------------
        struct msg_buffer message;
        message.msg_type = 1;

        printf("Parent: Enter a message to send: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);

        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        wait(NULL); // wait for child
        msgctl(msgid, IPC_RMID, NULL); // delete message queue
    }
    else if (pid == 0) {
        //---------------- Child : Receive message ---------------
        sleep(1); // allow parent to send first

        struct msg_buffer message;

        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

        printf("Child received: %s\n", message.msg_text);
    }

    return 0;
}

