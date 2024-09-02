#include <stdio.h>
#include <windows.h>
#include <winsock.h>


void EnviarOpcionYCantidadCaracteres (SOCKET Sock, int opcion, int cantidad_caracteres){
    send(Sock, (char*)&opcion, sizeof(opcion), 0);
    send(Sock, (char*)&cantidad_caracteres, sizeof(cantidad_caracteres), 0);
}



int main()
{
    //si te da el error de undefined reference to WSASartup tenes que darle segundo click al proyeto, tocar build option, vas a linker settings, y en linker libraries tocas add y pones ws2_32

    //Inicializar WinSock
    WSADATA WsaData;
    WORD  wVersionRequerida = MAKEWORD (2, 2);

    WSAStartup (wVersionRequerida, &WsaData);

    //creacion del socket
    SOCKET Sock;
    Sock = socket (AF_INET, SOCK_STREAM, 0);

    //especificar la direcion de la red del server 127.0.0.1 en el puerto 5000
    SOCKADDR_IN DireccionServer;
    memset (&DireccionServer, 0, sizeof (DireccionServer));
    DireccionServer.sin_family = AF_INET;
    DireccionServer.sin_addr.S_un.S_un_b.s_b1 = 127;
    DireccionServer.sin_addr.S_un.S_un_b.s_b2 = 0;
    DireccionServer.sin_addr.S_un.S_un_b.s_b3 = 0;
    DireccionServer.sin_addr.S_un.S_un_b.s_b4 = 1;
    DireccionServer.sin_port = htons(5000); //htons(5000)

    //inicia la conexion al socket que esta escuchando en el server
    int iResult = connect (Sock, (SOCKADDR*) &DireccionServer, sizeof(DireccionServer));
    if (iResult)
    {
        printf ("No se puede conectar\n");
        return 1;
    }



    while(1){


    system("cls");
    printf("Menu\n 1)Generador de nombres de usuario:\n 2)Generador de contraseñas:\n 3)Salir\n");

    //
    int opcion_menu;
    int cantidad_caracteres;
    char respuesta[80]={0};
    memset(respuesta, 0, sizeof(respuesta));

    scanf("%d",&opcion_menu);
    if(opcion_menu==1){
        printf("Seleccione cantidad de caracteres\n");
        scanf("%d",&cantidad_caracteres);
        EnviarOpcionYCantidadCaracteres(Sock,opcion_menu,cantidad_caracteres);

        recv(Sock, respuesta, sizeof(respuesta) - 1, 0);
        printf("su usuario es: %s\n",respuesta);
        system("pause");

    }else
    if(opcion_menu==2){
        printf("Seleccione cantidad de caracteres\n");
        scanf("%d",&cantidad_caracteres);
        EnviarOpcionYCantidadCaracteres(Sock,opcion_menu,cantidad_caracteres);
        recv(Sock, respuesta, sizeof(respuesta) - 1, 0);
        printf("su contraseña es: %s\n",respuesta);
        system("pause");
    }else
    if(opcion_menu==3){
            break;
    }
    else{
        system("cls");
        printf("opcion incorrecta.. vuelva a elegir\n");
        system("pause");
    }



    }



    closesocket (Sock); //cierra el socket
    WSACleanup(); //cierra la conexion

    return 0;
}
