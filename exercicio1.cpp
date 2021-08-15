#include <iostream>
#include <locale.h>
#include <new>
#include <time.h>
#include <string>
#include <fstream>


using namespace std;

#ifdef __unix__
    #include <unistd.h>
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32)

   #define OS_Windows

   #include <windows.h>

#endif

typedef struct Player{
    string name;

};

void clearScreen(){
    #ifdef OS_Windows
        system("cls");
    #else
        system("clear");
    #endif // OS_Windows

}

string returnWord(){
    string words[10] = {"banana", "maca", "carro", "amarelo", "privada", "computador", "notebook", "azul", "baleia", "leao"};

    int random = rand() % 10;
    return words[random];
}

string returnMasked(int *lenWord){
    string masked;

    for(int cont = 0; cont < *lenWord; cont++){
        masked += "_";
    }
    return masked;


}

void status(string *masked, string *alreadyUsed, int attempts, string *feedback){
    clearScreen();
    cout << *feedback << endl;
    cout << "Palavra: " << *masked << endl;
    cout << "Tentativas: " << attempts << endl;
    cout << "Letras já arriscadas: " << *alreadyUsed << endl;
    *feedback = "";

}

int selectPlayer(){

    int random_player = rand()%2;
    return random_player;

}

int play(int players){
    clearScreen();
    Player my_players[players];
    for (int c = 0; c < players; c++){
        string name_player;
        cout << "Nome Player " << c+1 << ":" << endl;
        cin >> name_player;
        my_players[c].name = name_player;
    }

    int *random_player = new int;
    bool *isFirstPlayer = new bool;
    *random_player = selectPlayer();
    string guessed;

    if (*random_player == 0){
        *isFirstPlayer = true;
    }

    if (players == 1){
      guessed = returnWord();
    }else{
      cout << my_players[*random_player].name << " escolhe uma palavra: ";
      cin >> guessed;
    }

    int lenWord = guessed.size();

    string masked = returnMasked(&lenWord);
    int attempts = 0;
    int max_attempts = 10;

    char *letter = new char;

    string alreadyUsed;

    bool *verifyLetter = new bool;
    string feedback;


    while (max_attempts - attempts > 0 && guessed != masked){

        status(&masked, &alreadyUsed, max_attempts-attempts, &feedback);

        cin >> *letter;
        clearScreen();

        for (int cont = 0; cont < attempts; cont++){
            if (alreadyUsed[cont] == *letter){
                feedback = "Essa letra já foi digitada!";
                *verifyLetter = true;
            }
        }

        if (*verifyLetter == false){
        alreadyUsed += tolower(*letter);
        for(int cont = 0; cont < lenWord; cont++){
            if(guessed[cont] == tolower(*letter)){
                masked[cont] = guessed[cont];
                #ifdef OS_Windows
                  Beep(523, 500);
                  cin.get();
                #else
                  system("echo -ne '\007'");
                  sleep(0.5);
                #endif
                feedback = "Você acertou uma letra!";
            }
        }

        attempts++;
        }
    }
    clearScreen();
    if (guessed == masked){
        if (players > 1 && *isFirstPlayer == false){
        cout << my_players[0].name << " venceu!" << endl;
        }else{
            if (players > 1 && *isFirstPlayer == true){
                cout << my_players[1].name << " venceu!" << endl;
            }else{
                cout << "Você venceu!" << endl;
            }
        }
    }else{
        if (players > 1 && *isFirstPlayer == false){
        cout << my_players[0].name << " perdeu!" << endl;
        }else{
            if (players > 1 && *isFirstPlayer == true){
                cout << my_players[1].name << " perdeu!" << endl;
            }else{
                cout << "Você perdeu!" << endl;
            }
        }
    }

    cout << "Deseja continuar?" << endl << "1-Sim" << endl << "2-Não" << endl;
    int *opcao = new int;

    cin >> *opcao;

    return *opcao;

}


void menu(){
    clearScreen();
    int *option = new int;

    cout << "Jogo da forca" << endl;
    cout << "1- Single Player" << endl << "2- Multiplayer" << endl << "3 - Sobre" << endl << "4 - Sair" << endl << "Escolha uma opção e tecle Enter:";
    cin >> *option;
    while (*option < 1 || *option > 3){
        cout << "Digite um valor válido!" << endl << "Tente novamente: ";
        cin >> *option;
    }

    cout << *option << endl;

    switch(*option){
    case 1:
        if(play(1)==1){
            menu();
        }
        break;
    case 2:
        if(play(2)==1){
            menu();
        }
        break;
    case 3:
        clearScreen();
        cout << "Desenvolvido por Gabriel Chaves em 2017\n" << endl;
        cout << "No modo multiplayer, a máquina seleciona aleatoriamente um dos dois jogadores" << endl;
        cout << "para digitar uma palavra, e o outro deverá adivinhá-la\n" << endl;
        cout << "1-Voltar" << endl << "2-Sair" << endl;
        cin >> *option;
        if (*option == 1){
            menu();
        }else{
            break;
        }
        break;
    case 4:
        cout << "Até mais" << endl;
        break;

    }

}

int main(){
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));
    menu();

    return 0;

}
