#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Jogador
{
    string nome;
    string nivel;
    int nTentativas;
    int pontuacao;
};

void guardarJogador(ofstream &f, const Jogador &jogador)
{
    f << jogador.nome << ";" << jogador.nivel << ";" << jogador.nTentativas << ";" << jogador.pontuacao << endl;
}

void mostrarJogador(const Jogador &jogador)
{
    cout << "\n--- Player Data ---\n";
    cout << "Name: " << jogador.nome << "\n";
    cout << "Level: " << jogador.nivel << "\n";
    cout << "Attempts: " << jogador.nTentativas << "\n";
    cout << "Score: " << jogador.pontuacao << "\n";
}

bool lerJogador(ifstream &f, Jogador &jogador)
{
    string linha;

    if (!getline(f, linha))
        return false;
    int pos;

    pos = linha.find(';');
    jogador.nome = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    
    pos = linha.find(';');
    jogador.nivel = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    
    pos = linha.find(';');
    string textoTentativas = linha.substr(0, pos);
    jogador.nTentativas = stoi(textoTentativas);
    linha.erase(0, pos + 1);
    
    jogador.pontuacao = stoi(linha);
    return true;
}

void mostrarRanking()
{
    Jogador temp;
    ifstream f("recordes.txt");

    if (!f.is_open())
    {
        cout << "No saved records yet.\n";
        return;
    }

    while (lerJogador(f, temp))
    {
        mostrarJogador(temp);
    }

    f.close();
}

void dadosdojogador(Jogador &jogador)
{
    cout << "--- WELCOME TO THE MEMORY GAME ---\n";
    cout << "\n======================================================\n";
    cout << endl
         << "Enter player name: ";
    getline(cin, jogador.nome);
}

const int LINHAS = 4;
const int COLUNAS = 4;
const int LINHASM = 4;
const int COLUNASM = 6;
const int LINHASD = 6;
const int COLUNASD = 6;
int qtdejogadas = 0;

void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS], const vector<char> &cartas)
{
    int k = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            tabuleiro[i][j] = cartas[k];
            k++;
        }
    }
}

void bemvindo()
{
    cout << "\n+----------------------------------+\n";
    cout << "|    WELCOME TO THE MEMORY GAME    |\n";
    cout << "+----------------------------------+\n";
    cout << "|         Developed by:            |\n";
    cout << "|              Illya               |\n";
    cout << "|            Cristiane             |\n";
    cout << "|              Ariane              |\n";
    cout << "+----------------------------------+\n";
}

int menu()
{
    int opcao;
    cout << "\n======================================================\n";
    cout << endl;
    cout << "\n--- Choose the game difficulty level ---" << endl
         << endl;
    cout << "1 - Easy" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Hard" << endl;
    cout << "4 - View Ranking" << endl;
    cout << "0 - Exit Game" << endl;
    cout << "\n";
    cout << "========================================================\n";
    cout << "               Choose an option: ";
    cin >> opcao;
    cout << "========================================================\n";
    cout << "\n";
    return opcao;
}

void inicializarTabuleiroM(string tabuleiroM[LINHASM][COLUNASM], const vector<string> &cartasM)
{
    int k = 0;
    for (int i = 0; i < LINHASM; i++)
    {
        for (int j = 0; j < COLUNASM; j++)
        {
            tabuleiroM[i][j] = cartasM[k];
            k++;
        }
    }
}

void inicializarTabuleiroD(string tabuleiroD[LINHASD][COLUNASD], const vector<string> &cartasD)
{
    int k = 0;
    for (int i = 0; i < LINHASD; i++)
    {
        for (int j = 0; j < COLUNASD; j++)
        {
            tabuleiroD[i][j] = cartasD[k];
            k++;
        }
    }
}

void exibirTabuleiro(char tabuleiro[LINHAS][COLUNAS], bool reveladas[LINHAS][COLUNAS])
{
    cout << "\n    0   1   2   3\n";
    cout << "  -----------------\n";
    for (int i = 0; i < LINHAS; i++)
    {
        cout << i << " | ";
        for (int j = 0; j < COLUNAS; j++)
        {
            if (reveladas[i][j])
            {
                cout << tabuleiro[i][j] << "   ";
            }
            else
            {
                cout << "*   ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void exibirTabuleiroM(string tabuleiroM[LINHASM][COLUNASM], bool reveladasM[LINHASM][COLUNASM])
{
    cout << "\n     0    1    2    3    4    5\n";
    cout << "  --------------------------------\n";
    for (int i = 0; i < LINHASM; i++)
    {
        cout << i << " | ";
        for (int j = 0; j < COLUNASM; j++)
        {
            if (reveladasM[i][j])
            {
                cout << tabuleiroM[i][j] << "   ";
            }
            else
            {
                cout << " *   ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void exibirTabuleiroD(string tabuleiroD[LINHASD][COLUNASD], bool reveladasD[LINHASD][COLUNASD])
{
    cout << "\n     0    1    2    3    4    5\n";
    cout << "  --------------------------------\n";
    for (int i = 0; i < LINHASD; i++)
    {
        cout << i << " | ";
        for (int j = 0; j < COLUNASD; j++)
        {
            if (reveladasD[i][j])
            {
                cout << tabuleiroD[i][j] << "   ";
            }
            else
            {
                cout << " *   ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void guardarRecorde(Jogador &jogador, string nivel, int pontos)
{
    jogador.nivel = nivel;
    jogador.nTentativas = qtdejogadas;
    jogador.pontuacao = pontos;
    ofstream f("recordes.txt", ios::app);
    guardarJogador(f, jogador);
    f.close();
}

void fim(int qtdejogadas)
{
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|                       GAME OVER                          |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|                  Thanks for playing!                     |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|  Congratulations! Found all pairs and won the game!      |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|     You made " << qtdejogadas << " attempts.               |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
}

int main()
{
    Jogador jogador1;
    char facil[] = {'1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8'};
    vector<char> cartas(facil, facil + sizeof(facil) / sizeof(char));

    string medio[] = {"10", "10", "11", "11", "12", "12", "13", "13", "14", "14", "15", "15", "16", "16", "17", "17", "18", "18", "19", "19", "20", "20", "21", "21"};
    vector<string> cartasM(medio, medio + sizeof(medio) / sizeof(string));

    string dificil[] = {"10", "10", "11", "11", "12", "12", "13", "13", "14", "14", "15", "15", "16", "16", "17", "17", "18", "18", "19", "19", "20", "20", "21", "21", "22", "22", "23", "23", "24", "24", "25", "25", "26", "26", "27", "27"};
    vector<string> cartasD(dificil, dificil + sizeof(dificil) / sizeof(string));

    srand(time(0));

    for (size_t i = 0; i < cartas.size(); i++)
    {
        size_t j = rand() % cartas.size();
        swap(cartas[i], cartas[j]);
    }

    for (size_t i = 0; i < cartasM.size(); i++)
    {
        size_t j = rand() % cartasM.size();
        swap(cartasM[i], cartasM[j]);
    }

    for (size_t i = 0; i < cartasD.size(); i++)
    {
        size_t j = rand() % cartasD.size();
        swap(cartasD[i], cartasD[j]);
    }

    char tabuleiro[LINHAS][COLUNAS];
    string tabuleiroM[LINHASM][COLUNASM];
    string tabuleiroD[LINHASD][COLUNASD];

    bool reveladas[LINHAS][COLUNAS];
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            reveladas[i][j] = false;
        }
    }

    bool reveladasM[LINHASM][COLUNASM];
    for (int i = 0; i < LINHASM; i++)
    {
        for (int j = 0; j < COLUNASM; j++)
        {
            reveladasM[i][j] = false;
        }
    }

    bool reveladasD[LINHASD][COLUNASD];
    for (int i = 0; i < LINHASD; i++)
    {
        for (int j = 0; j < COLUNASD; j++)
        {
            reveladasD[i][j] = false;
        }
    }

    inicializarTabuleiro(tabuleiro, cartas);
    inicializarTabuleiroM(tabuleiroM, cartasM);
    inicializarTabuleiroD(tabuleiroD, cartasD);

    int paresEncontrados = 0;
    int erros = 0;
    int pontuacao = 0;
    int totalPares = (LINHAS * COLUNAS) / 2;
    int totalParesM = (LINHASM * COLUNASM) / 2;
    int totalParesD = (LINHASD * COLUNASD) / 2;

    dadosdojogador(jogador1);
    bemvindo();
    int opcao = menu();

    switch (opcao)
    {
    case 1:
        cout << "Choice: Easy" << endl
             << endl;
        cout << "Number of pairs: 8 " << endl
             << endl;

        while (paresEncontrados < totalPares)
        {
            exibirTabuleiro(tabuleiro, reveladas);

            int l1, c1, l2, c2;

            cout << "Choose the first card (row and column separated by space, e.g., 0 2): ";
            cin >> l1 >> c1;

            if (l1 < 0 || l1 >= LINHAS || c1 < 0 || c1 >= COLUNAS)
            {
                cout << "Invalid position! Choose values between 0 and 3.\n";
                continue;
            }

            if (reveladas[l1][c1])
            {
                cout << "This card has already been revealed! Try another.\n";
                continue;
            }

            reveladas[l1][c1] = true;
            exibirTabuleiro(tabuleiro, reveladas);

            cout << "Choose the second card (row and column separated by space): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHAS || c2 < 0 || c2 >= COLUNAS)
            {
                cout << "Invalid position! Choose values between 0 and 3.\n";
                reveladas[l1][c1] = false;
                continue;
            }

            if (reveladas[l2][c2])
            {
                cout << "This card has already been revealed or is the same! Try another.\n";
                reveladas[l1][c1] = false;
                continue;
            }

            reveladas[l2][c2] = true;
            exibirTabuleiro(tabuleiro, reveladas);

            if (tabuleiro[l1][c1] == tabuleiro[l2][c2])
            {
                cout << "Nice! Found a pair!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 10;
            }
            else
            {
                cout << "Wrong! Cards do not match.\n";
                reveladas[l1][c1] = false;
                reveladas[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 2;
            }
            cout << "\n";
            cout << "Player Name: " << jogador1.nome << endl;
            cout << "Chosen level: Easy" << endl;
            cout << "Attempts: " << qtdejogadas << endl;
            cout << "Errors: " << erros << endl;
            cout << "Pairs found: " << paresEncontrados << endl;
            cout << "Score: " << pontuacao << endl;
        }
        fim(qtdejogadas);
        guardarRecorde(jogador1, "Facil", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 2:
        cout << "Choice: Medium" << endl
             << endl;
        cout << "Number of pairs: 12 " << endl
             << endl;

        while (paresEncontrados < totalParesM)
        {
            exibirTabuleiroM(tabuleiroM, reveladasM);

            int l1, c1, l2, c2;

            cout << "Choose the first card (row and column separated by space, e.g., 0 2): ";
            cin >> l1 >> c1;

            if (l1 < 0 || l1 >= LINHASM || c1 < 0 || c1 >= COLUNASM)
            {
                cout << "Invalid position! Choose values between 0 and 5.\n";
                continue;
            }

            if (reveladasM[l1][c1])
            {
                cout << "This card has already been revealed! Try another.\n";
                continue;
            }

            reveladasM[l1][c1] = true;
            exibirTabuleiroM(tabuleiroM, reveladasM);

            cout << "Choose the second card (row and column separated by space): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHASM || c2 < 0 || c2 >= COLUNASM)
            {
                cout << "Invalid position! Choose values between 0 and 5.\n";
                reveladasM[l1][c1] = false;
                continue;
            }

            if (reveladasM[l2][c2])
            {
                cout << "This card has already been revealed or is the same! Try another.\n";
                reveladasM[l1][c1] = false;
                continue;
            }

            reveladasM[l2][c2] = true;
            exibirTabuleiroM(tabuleiroM, reveladasM);

            if (tabuleiroM[l1][c1] == tabuleiroM[l2][c2])
            {
                cout << "Nice! Found a pair!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 20;
            }
            else
            {
                cout << "Wrong! Cards do not match.\n";
                reveladasM[l1][c1] = false;
                reveladasM[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 3;
            }
            cout << "\n";
            cout << "Player Name: " << jogador1.nome << endl;
            cout << "Chosen level: Medium" << endl;
            cout << "Attempts: " << qtdejogadas << endl;
            cout << "Errors: " << erros << endl;
            cout << "Pairs found: " << paresEncontrados << endl;
            cout << "Score: " << pontuacao << endl;
        }
        fim(qtdejogadas);
        guardarRecorde(jogador1, "Medio", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 3:
        cout << "Choice: Hard" << endl
             << endl;
        cout << "Number of pairs: 18 " << endl
             << endl;

        while (paresEncontrados < totalParesD)
        {
            exibirTabuleiroD(tabuleiroD, reveladasD);

            int l1, c1, l2, c2;

            cout << "Choose the first card (row and column separated by space, e.g., 0 2): ";
            cin >> l1 >> c1;

            if (l1 < 0 || l1 >= LINHASD || c1 < 0 || c1 >= COLUNASD)
            {
                cout << "Invalid position! Choose values between 0 and 5.\n";
                continue;
            }

            if (reveladasD[l1][c1])
            {
                cout << "This card has already been revealed! Try another.\n";
                continue;
            }

            reveladasD[l1][c1] = true;
            exibirTabuleiroD(tabuleiroD, reveladasD);

            cout << "Choose the second card (row and column separated by space): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHASD || c2 < 0 || c2 >= COLUNASD)
            {
                cout << "Invalid position! Choose values between 0 and 5.\n";
                reveladasD[l1][c1] = false;
                continue;
            }

            if (reveladasD[l2][c2])
            {
                cout << "This card has already been revealed or is the same! Try another.\n";
                reveladasD[l1][c1] = false;
                continue;
            }

            reveladasD[l2][c2] = true;
            exibirTabuleiroD(tabuleiroD, reveladasD);

            if (tabuleiroD[l1][c1] == tabuleiroD[l2][c2])
            {
                cout << "Nice! Found a pair!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 30;
            }
            else
            {
                cout << "Wrong! Cards do not match.\n";
                reveladasD[l1][c1] = false;
                reveladasD[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 4;
            }
            cout << "\n";
            cout << "Player Name: " << jogador1.nome << endl;
            cout << "Chosen level: Hard" << endl;
            cout << "Attempts: " << qtdejogadas << endl;
            cout << "Errors: " << erros << endl;
            cout << "Pairs found: " << paresEncontrados << endl;
            cout << "Score: " << pontuacao << endl;
        }

        fim(qtdejogadas);
        guardarRecorde(jogador1, "Dificil", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 4:
        mostrarRanking();
        break;
    case 0:
        cout << "Exiting game..." << endl;
        break;
    default:
        cout << "Invalid option! Try again." << endl;
    }

    return 0;
}
