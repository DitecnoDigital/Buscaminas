#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void LimpiarPantalla();
void Configuracion();
void JugarPartida();
bool ComprobarCasillas();
void MostrarTablero(bool mostrarBombas);
int DescubrirCasilla();
void LlenarTablero();
void VaciarSector(int y,int x);

vector<vector<int>> tablero;

char eleccion;
vector<int> tamTablero(2);
vector<int> posCasilla(2);
int cantMinas = 0;
bool tableroConBombas = false;
vector<vector<int>> operaciones = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};


int main(){
    while(true){
        LimpiarPantalla();
        cout<<"::::BUSCAMINAS::::"<<endl;
        cout<<"1) Jugar"<<endl;
        cout<<"2) Salir"<<endl;
        cout<<"Eleccion: ";
        cin>>eleccion;
        switch(eleccion){
            case '1':
            Configuracion();
            JugarPartida();
            break;
            case '2':
            return 0;
            break;
        }
    }
    return 0;
}

void LimpiarPantalla(){
    if(system("clear") == -1){
        cout<<"Error al borrar pantalla"<<endl;
    }
}

void Configuracion(){
    LimpiarPantalla();
    cout<<"::::CONFIGURACION::::"<<endl;
    cout<<"Ingrese el tamaño del tablero: ";
    cin>>tamTablero[0]>>tamTablero[1];
    cout<<"Ingrese la cantidad de minas: ";
    cin>>cantMinas;
    tablero.resize(tamTablero[0],(vector<int>(tamTablero[1])));
    for(int i = 0; i < tamTablero[0]; i++){
        for(int j = 0; j < tamTablero[1]; j++){
            tablero[i][j] = -1;
        }
    }
}

void JugarPartida(){
    tableroConBombas = false;
    while(ComprobarCasillas()){
        MostrarTablero(false);
        cout<<"\n1) Descubrir Casilla"<<endl;
        cout<<"2) Marcar Casilla"<<endl;
        cout<<"3) Desmarcar Casilla"<<endl;
        cout<<"Eleccion: ";
        cin>>eleccion;
        int retorno;
        switch(eleccion){
            case '1':
            cout<<"Ingrese la posicion de la casilla a descubrir: ";
            cin>>posCasilla[0]>>posCasilla[1];
            retorno = DescubrirCasilla();
            if(retorno == -1){
                return;
            }else if(retorno == 2 && tableroConBombas){
                VaciarSector(posCasilla[0],posCasilla[1]);
            }
            if(!tableroConBombas){
                LlenarTablero();
                tablero[posCasilla[0]][posCasilla[1]] = -1;
                tableroConBombas = true;
                retorno = DescubrirCasilla();
                if(retorno == -1){
                    return;
                }else if(retorno == 2 && tableroConBombas){
                    VaciarSector(posCasilla[0],posCasilla[1]);
                }
            }
            break;
            case '2':
            cout<<"Ingrese la posicion de la casilla a marcar: ";
            cin>>posCasilla[0]>>posCasilla[1];
            if(tablero[posCasilla[0]][posCasilla[1]] == 10){
                tablero[posCasilla[0]][posCasilla[1]] = 1011;
            }else if(tablero[posCasilla[0]][posCasilla[1]] == -1){
                tablero[posCasilla[0]][posCasilla[1]] = 11;
            }
            break;
            case '3':
            cout<<"Ingrese la posicion de la casilla a desmarcar: ";
            cin>>posCasilla[0]>>posCasilla[1];
            if(tablero[posCasilla[0]][posCasilla[1]] == 11){
                tablero[posCasilla[0]][posCasilla[1]] = -1;
            }else if(tablero[posCasilla[0]][posCasilla[1]] == 1011){
                tablero[posCasilla[0]][posCasilla[1]] = 10;
            }
            break;
        }
    }
    cout<<"\n 🍾🥳 FELICITACIONES HAS GANADO 🥳🍾 Ingrese OK para continuar: ";
    cin>>eleccion;
}

bool ComprobarCasillas(){
    for(int i = 0; i < tamTablero[0]; i++){
        for(int j = 0; j < tamTablero[1]; j++){
            cout<<tablero[i][j]<<endl;
            if(tablero[i][j] == -1){
                return true;
            }
        }
    }
    return false;
}

void MostrarTablero(bool mostrarBombas){
    LimpiarPantalla();
    for(int i = 0; i < tamTablero[1]; i++){
        cout<<" "<<i;
    }
    cout<<endl;
    for(int i = 0; i < tamTablero[0]; i++){
        for(int j = 0; j < tamTablero[1]; j++){
            switch(tablero[i][j]){
                case -1:
                cout<<"⬜";
                break;
                case 0:
                cout<<"⬛";
                break;
                case 1:
                cout<<"1️⃣ ";
                break;
                case 2:
                cout<<"2️⃣ ";
                break;
                case 3:
                cout<<"3️⃣ ";
                break;
                case 4:
                cout<<"4️⃣ ";
                break;
                case 5:
                cout<<"​5️⃣ ";
                break;
                case 6:
                cout<<"6️⃣ ";
                break;
                case 7:
                cout<<"7️⃣ ";
                break;
                case 8:
                cout<<"8️⃣ ";
                break;
                case 10:
                if(mostrarBombas){
                    cout<<"💣";
                }else{
                    cout<<"⬜";
                }
                break;
                case 1011:
                if(mostrarBombas){
                    cout<<"💣";
                }else{
                    cout<<"🚩";
                }
                break;
                case 11:
                cout<<"🚩";
                break;
            }
        }
        cout<<" "<<i;
        cout<<endl;
    }
}

int DescubrirCasilla(){
    int cont = 0;
    switch(tablero[posCasilla[0]][posCasilla[1]]){
        case 11:
        case 1011:
        cout<<"Casilla marcada, no es posible descubrirla. Ingrese OK: ";
        cin>>eleccion;
        break;
        case 10:
        MostrarTablero(true);
        cout<<"\n😱 Perdiste 😱 Ingrese OK: ";
        cin>>eleccion;
        return -1;
        break;
        case -1:
        for(int i = 0; i < 8; i++){
            if(posCasilla[0]+ operaciones[i][0] >= 0 && posCasilla[0]+ operaciones[i][0] < tamTablero[0]){
                if(posCasilla[1]+ operaciones[i][1] >= 0 && posCasilla[1]+ operaciones[i][1] < tamTablero[1]){
                    if(tablero[posCasilla[0]+operaciones[i][0]][posCasilla[1]+operaciones[i][1]] == 10 || tablero[posCasilla[0]+operaciones[i][0]][posCasilla[1]+operaciones[i][1]] == 1011){
                        cont++;
                    }
                }   
            }
        }
        tablero[posCasilla[0]][posCasilla[1]] = cont;
        return 2;
        break;
        default:
        cout<<"Esa casilla ya fue descubierta. Ingrese OK: ";
        cin>>eleccion;
        break;
    }
    return 0;
}

void LlenarTablero(){
    srand(time(NULL));
    for(int i = 0; i < cantMinas; i++){
        int x,y;
        do{
            y = rand() % tamTablero[0];
            x = rand() % tamTablero[1];
        }while(tablero[y][x] == 0 || tablero[y][x] == 10);

        tablero[y][x] = 10;
    }
}

void VaciarSector(int y,int x){
    int cont = 0;
    for(int i = 0; i < 8; i++){
        if(y + operaciones[i][0] >= 0 && y+ operaciones[i][0] < tamTablero[0]){
            if(x+ operaciones[i][1] >= 0 && x + operaciones[i][1] < tamTablero[1]){
                if(tablero[y+operaciones[i][0]][x+operaciones[i][1]] == 10 || tablero[y+operaciones[i][0]][x+operaciones[i][1]] == 1011){
                    cont++;
                }
            }   
        }
    }
    if(cont == 0){
        tablero[y][x] = 0;
        for(int i = 0; i < 8; i++){
            if(y + operaciones[i][0] >= 0 && y+ operaciones[i][0] < tamTablero[0]){
                if(x+ operaciones[i][1] >= 0 && x + operaciones[i][1] < tamTablero[1]){
                    if(tablero[y+operaciones[i][0]][x+operaciones[i][1]] == -1){
                        VaciarSector(y+operaciones[i][0],x+operaciones[i][1]);
                    }
                }
            }
        }
    }else{
        tablero[y][x] = cont;
        return;
    }
}