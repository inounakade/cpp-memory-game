#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib> //Biblioteca do o rand e srand, função esconde/exibe n.ºs
#include <fstream>

using namespace std;

struct Jogador
{
    string nome;
    string nivel;
    int nTentativas;
    int pontuacao;
};
/* guarda e escreve num ficheiro o nome nivel tentatias e ponctuacao */
void guardarJogador(ofstream &f, const Jogador &jogador)
{
    f << jogador.nome << ";" << jogador.nivel << ";" << jogador.nTentativas << ";" << jogador.pontuacao << endl;
}
/* mostra os dados do jogador */
void mostrarJogador(const Jogador &jogador)
{
    cout << "\n--- Dados do Jogador ---\n";
    cout << "Nome: " << jogador.nome << "\n";
    cout << "Nível: " << jogador.nivel << "\n";
    cout << "Número de Tentativas: " << jogador.nTentativas << "\n";
    cout << "Pontuação: " << jogador.pontuacao << "\n";
}

bool lerJogador(ifstream &f, Jogador &jogador)
{
    string linha;

    if (!getline(f, linha))
        return false;
    int pos;

    // Encontra o primeiro ';' e corta o nome
    pos = linha.find(';');
    jogador.nome = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    // Repete o processo para o nivel da dificuldade
    pos = linha.find(';');
    jogador.nivel = linha.substr(0, pos);
    linha.erase(0, pos + 1);
    // Extrai o numero em formato de texto e apaga da linha
    pos = linha.find(';');
    string textoTentativas = linha.substr(0, pos);
    // Pesquisa extra: a funcao stoi() converte a string num int
    jogador.nTentativas = stoi(textoTentativas);
    linha.erase(0, pos + 1);
    // Como apaga tudo o resto, a linha agora so contem a pontuacao final
    jogador.pontuacao = stoi(linha);
    return true;
}


void mostrarRanking()
{
    Jogador temp;
    ifstream f("recordes.txt");

    if (!f.is_open())
    {
        cout << "Ainda nao ha resultados guardados.\n";
        return;
    }

    while (lerJogador(f, temp))
    {
        mostrarJogador(temp);
    }

    f.close();
}

/* onde o utilizador insira o seu nome */
void dadosdojogador(Jogador &jogador)
{
    cout << "--- BEM-VINDO AO JOGO DA MEMÓRIA ---\n";

    cout << "\n======================================================\n";
    cout << endl
         << "Insira o nome do Jogador: ";
    getline(cin, jogador.nome);
}

// Variáveis do jogo - const torna a variável imutável (valor não pode ser alterado)
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
/* messagem de bem vindo */
void bemvindo()
{
    cout << "\n+----------------------------------+\n";
    cout << "|   BEM-VINDO AO JOGO DA MEMORIA   |\n";
    cout << "+----------------------------------+\n";
    cout << "|         Desenvolvido por:        |\n";
    cout << "|              Illya               |\n";
    cout << "|            Cristiane             |\n";
    cout << "|              Ariane              |\n";
    cout << "+----------------------------------+\n";
}
/* menu do jogo */
int menu()
{
    int opcao;
    cout << "\n======================================================\n";
    cout << endl;
    cout << "\n--- Escolha o número do nível de dificuldade do jogo ---" << endl
         << endl;
    cout << "1 - Fácil" << endl;
    cout << "2 - Médio" << endl;
    cout << "3 - Difícil" << endl;
    cout << "4 - Ver Ranking" << endl;
    cout << "0 - Sair do Jogo" << endl;
    cout << "\n";
    cout << "========================================================\n";
    cout << "               Escolha uma opção: ";
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
                cout << "*   "; // Aqui esconde a carta
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
                cout << " *   "; // Aqui esconde a carta
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
                cout << " *   "; // Aqui esconde a carta
            }
        }
        cout << "\n";
    }
    cout << "\n";
}
/* guarda os dados do jugador */
void guardarRecorde(Jogador &jogador, string nivel, int pontos)
{
    jogador.nivel = nivel;
    jogador.nTentativas = qtdejogadas;
    jogador.pontuacao = pontos;
    ofstream f("recordes.txt", ios::app);
    guardarJogador(f, jogador);
    f.close();
}
/* fim do jogo que guarde numero de tentativas */
void fim(int qtdejogadas)
{
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|                       GAME OVER                          |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|                  Obrigado por jogar!                     |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|  Parabéns! Encontrou todos os pares e venceu o jogo!     |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "+----------------------------------------------------------+" << endl;
    cout << "|     Você fez " << qtdejogadas << " tentativas.           |" << endl;
    cout << "+----------------------------------------------------------+" << endl;
}

int main()
{
    Jogador jogador1;
    // Iniciando o vetor
    char facil[] = {'1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8'};
    vector<char> cartas(facil, facil + sizeof(facil) / sizeof(char));

    // Iniciando o vetor
    string medio[] = {"10", "10", "11", "11", "12", "12", "13", "13", "14", "14", "15", "15", "16", "16", "17", "17", "18", "18", "19", "19", "20", "20", "21", "21"};
    vector<string> cartasM(medio, medio + sizeof(medio) / sizeof(string));

    // Iniciando o vetor
    string dificil[] = {"10", "10", "11", "11", "12", "12", "13", "13", "14", "14", "15", "15", "16", "16", "17", "17", "18", "18", "19", "19", "20", "20", "21", "21", "22", "22", "23", "23", "24", "24", "25", "25", "26", "26", "27", "27"};
    vector<string> cartasD(dificil, dificil + sizeof(dificil) / sizeof(string));

    // Gera os números aleatórios
    srand(time(0));

    // Esse for é para embaralhar
    for (size_t i = 0; i < cartas.size(); i++)
    {
        size_t j = rand() % cartas.size();
        swap(cartas[i], cartas[j]);
        // Para trocar o valor das variáveis
    }

    // Esse for é para embaralhar
    for (size_t i = 0; i < cartasM.size(); i++)
    {
        size_t j = rand() % cartasM.size();
        swap(cartasM[i], cartasM[j]);
        // Para trocar o valor das variáveis
    }

    // Esse for é para embaralhar
    for (size_t i = 0; i < cartasD.size(); i++)
    {
        size_t j = rand() % cartasD.size();
        swap(cartasD[i], cartasD[j]);
        // Para trocar o valor das variáveis
    }

    // Declarei a matriz tabuleiro
    char tabuleiro[LINHAS][COLUNAS];

    // Declarei a matriz tabuleiro
    string tabuleiroM[LINHASM][COLUNASM];

    // Declarei a matriz tabuleiro
    string tabuleiroD[LINHASD][COLUNASD];

    // Inicia a matriz escondendo, mostra somente os *****
    bool reveladas[LINHAS][COLUNAS];
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            reveladas[i][j] = false;
        }
    }

    // Inicia a matriz escondendo, mostra somente os *****
    bool reveladasM[LINHASM][COLUNASM];
    for (int i = 0; i < LINHASM; i++)
    {
        for (int j = 0; j < COLUNASM; j++)
        {
            reveladasM[i][j] = false;
        }
    }

    // Inicia a matriz escondendo, mostra somente os *****
    bool reveladasD[LINHASD][COLUNASD];
    for (int i = 0; i < LINHASD; i++)
    {
        for (int j = 0; j < COLUNASD; j++)
        {
            reveladasD[i][j] = false;
        }
    }

    // Carregou o valor de tabuleiro e cartas (matriz e vetor)
    inicializarTabuleiro(tabuleiro, cartas);

    // Carregou o valor de tabuleiro e cartas (matriz e vetor)
    inicializarTabuleiroM(tabuleiroM, cartasM);

    // Carregou o valor de tabuleiro e cartas (matriz e vetor)
    inicializarTabuleiroD(tabuleiroD, cartasD);

    // Definiu as variáveis
    int paresEncontrados = 0;
    int erros = 0;
    int pontuacao = 0;
    int totalPares = (LINHAS * COLUNAS) / 2;
    int totalParesM = (LINHASM * COLUNASM) / 2;
    int totalParesD = (LINHASD * COLUNASD) / 2;

    dadosdojogador(jogador1);
    bemvindo();
    int opcao = menu();

    // Iniciando o Programa
    switch (opcao)
    {
    case 1:
        cout << "Escolha: Fácil" << endl
             << endl;
        cout << "Número de pares: 8 " << endl
             << endl;

        // Estabeleceu a condição
        while (paresEncontrados < totalPares)
        {
            exibirTabuleiro(tabuleiro, reveladas);

            int l1, c1, l2, c2;

            cout << "Escolha a primeira carta (linha e coluna separadas por espaco, ex: 0 2): ";
            cin >> l1 >> c1;

            // Valida se o Jogador digita linha e colunas válidas do tabuleiro
            if (l1 < 0 || l1 >= LINHAS || c1 < 0 || c1 >= COLUNAS)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 3.\n";
                continue;
            }

            if (reveladas[l1][c1])
            {
                cout << "Essa carta já foi revelada! Tente outra.\n";
                continue;
            }

            reveladas[l1][c1] = true;
            exibirTabuleiro(tabuleiro, reveladas);

            cout << "Escolha a segunda carta (linha e coluna separadas por espaco): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHAS || c2 < 0 || c2 >= COLUNAS)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 3.\n";
                reveladas[l1][c1] = false; // Esconde a primeira carta
                continue;
            }

            if (reveladas[l2][c2])
            {
                cout << "Essa carta já foi revelada ou é a mesma! Tente outra.\n";
                reveladas[l1][c1] = false;
                continue;
            }

            reveladas[l2][c2] = true;
            exibirTabuleiro(tabuleiro, reveladas);

            // Conferir se acertou o par
            if (tabuleiro[l1][c1] == tabuleiro[l2][c2])
            {
                cout << "Boa! Encontrou um par!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 10;
            }
            else
            {
                cout << "Errado! As cartas não são iguais.\n";
                reveladas[l1][c1] = false; // Esconde a carta
                reveladas[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 2;
            }
            cout << "\n";
            cout << "Nome do Jogador: " << jogador1.nome << endl;
            cout << "O nível escolhido é: Fácil" << endl;
            cout << "Tentativas: " << qtdejogadas << endl;
            cout << "Erros: " << erros << endl;
            cout << "Pares encontrados: " << paresEncontrados << endl;
            cout << "Pontuação: " << pontuacao << endl;
        }
        fim(qtdejogadas);
        guardarRecorde(jogador1, "Facil", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 2:
        cout << "Escolha: Médio" << endl
             << endl;
        cout << "Número de pares: 12 " << endl
             << endl;

        // Estabeleceu a condição
        while (paresEncontrados < totalParesM)
        {
            exibirTabuleiroM(tabuleiroM, reveladasM);

            int l1, c1, l2, c2;

            cout << "Escolha a primeira carta (linha e coluna separadas por espaco, ex: 0 2): ";
            cin >> l1 >> c1;

            // Valida se o Jogador digita linha e colunas válidas do tabuleiro
            if (l1 < 0 || l1 >= LINHASM || c1 < 0 || c1 >= COLUNASM)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 5.\n";
                continue;
            }

            if (reveladasM[l1][c1])
            {
                cout << "Essa carta já foi revelada! Tente outra.\n";
                continue;
            }

            reveladasM[l1][c1] = true;
            exibirTabuleiroM(tabuleiroM, reveladasM);

            cout << "Escolha a segunda carta (linha e coluna separadas por espaco): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHASM || c2 < 0 || c2 >= COLUNASM)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 3.\n";
                reveladasM[l1][c1] = false; // Esconde a primeira carta
                continue;
            }

            if (reveladasM[l2][c2])
            {
                cout << "Essa carta já foi revelada ou é a mesma! Tente outra.\n";
                reveladasM[l1][c1] = false;
                continue;
            }

            reveladasM[l2][c2] = true;
            exibirTabuleiroM(tabuleiroM, reveladasM);

            // Conferir se acertou o par
            if (tabuleiroM[l1][c1] == tabuleiroM[l2][c2])
            {
                cout << "Boa! Encontrou um par!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 20;
            }
            else
            {
                cout << "Errado! As cartas não são iguais.\n";
                reveladasM[l1][c1] = false; // Esconde a carta
                reveladasM[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 3;
            }
            cout << "\n";
            cout << "Nome do Jogador: " << jogador1.nome << endl;
            cout << "O nível escolhido é: Médio" << endl;
            cout << "Tentativas: " << qtdejogadas << endl;
            cout << "Erros: " << erros << endl;
            cout << "Pares encontrados: " << paresEncontrados << endl;
            cout << "Pontuação: " << pontuacao << endl;
        }
        fim(qtdejogadas);
        guardarRecorde(jogador1, "Medio", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 3:
        cout << "Escolha: Difícil" << endl
             << endl;
        cout << "Número de pares: 18 " << endl
             << endl;

        // Estabeleceu a condição
        while (paresEncontrados < totalParesD)
        {
            exibirTabuleiroD(tabuleiroD, reveladasD);

            int l1, c1, l2, c2;

            cout << "Escolha a primeira carta (linha e coluna separadas por espaco, ex: 0 2): ";
            cin >> l1 >> c1;

            // Valida se o Jogador digita linha e colunas válidas do tabuleiro
            if (l1 < 0 || l1 >= LINHASD || c1 < 0 || c1 >= COLUNASD)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 5.\n";
                continue;
            }

            if (reveladasD[l1][c1])
            {
                cout << "Essa carta já foi revelada! Tente outra.\n";
                continue;
            }

            reveladasD[l1][c1] = true;
            exibirTabuleiroD(tabuleiroD, reveladasD);

            cout << "Escolha a segunda carta (linha e coluna separadas por espaco): ";
            cin >> l2 >> c2;

            if (l2 < 0 || l2 >= LINHASD || c2 < 0 || c2 >= COLUNASD)
            {
                cout << "Posição inválida! Escolha valores entre 0 e 3.\n";
                reveladasD[l1][c1] = false; // Esconde a primeira carta
                continue;
            }

            if (reveladasD[l2][c2])
            {
                cout << "Essa carta já foi revelada ou é a mesma! Tente outra.\n";
                reveladasD[l1][c1] = false;
                continue;
            }

            reveladasD[l2][c2] = true;
            exibirTabuleiroD(tabuleiroD, reveladasD);

            // Conferir se acertou o par
            if (tabuleiroD[l1][c1] == tabuleiroD[l2][c2])
            {
                cout << "Boa! Encontrou um par!\n";
                paresEncontrados++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao + 30;
            }
            else
            {
                cout << "Errado! As cartas não são iguais.\n";
                reveladasD[l1][c1] = false; // Esconde a carta
                reveladasD[l2][c2] = false;
                erros++;
                qtdejogadas = qtdejogadas + 1;
                pontuacao = pontuacao - 4;
            }
            cout << "\n";
            cout << "Nome do Jogador: " << jogador1.nome << endl;
            cout << "O nível escolhido é: Difícil" << endl;
            cout << "Tentativas: " << qtdejogadas << endl;
            cout << "Erros: " << erros << endl;
            cout << "Pares encontrados: " << paresEncontrados << endl;
            cout << "Pontuação: " << pontuacao << endl;
        }

        fim(qtdejogadas);
        guardarRecorde(jogador1, "Dificil", pontuacao);
        mostrarJogador(jogador1);
        break;
    case 4:
        mostrarRanking();
        break;
    case 0:
        cout << "Saindo do Jogo..." << endl;
        break;
    default:
        cout << "Opcao inválida! Tente novamente." << endl;
    }

    return 0;
}
