#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <stdio.h>
#include <ctime>


using namespace std;


// Function for play -> train -> RPS (用來判斷猜拳勝負 

int result(int com,int you){
	if(com == you){
		return 0;
	}
	else if((you == 2 && com == 1)||(you == 3 && com == 2)||(you == 1 && com == 3)){
		return 1;
	}
	else{
		return 2;
	}
}
// Function for play -> train (猜拳 
int RPS(){
	int you;
	int com;
	int r;
	do{
	srand(time(0));
	com = (rand()%3)+1;	
	cout<<"choose one you like by the following:\n(1)Rock\n(2)Paper\n(3)Scissors\n";
	do{
	cin>>you;
	}while(you != 1 && you != 2 && you != 3);
	
	if(com == 1){
		cout<<"the opponent : Rock\n";
	}
	else if(com == 2){
		cout<<"the opponent : Paper\n";
	}
	else if(com == 3){
		cout<<"the opponent : Scissors\n";
	}
	if(you == 1){
		cout<<"you : Rock\n";
	}
	else if(you == 2){
		cout<<"you : Paper\n";
	}
	else if(you == 3){
		cout<<"you : Scissors\n";
	}
	if(result(com,you) == 0){
		cout<<"Tie, Get 20 $ \n";
		return 20;
	}
	else if(result(com,you) == 1){
		cout<<"You win, Get 20 $ \n";
		return 100;
	}
	else if(result(com,you) == 2){
		cout<<"You lose, Get 0 $ \n";
		return 0;
	}
	}while(result(com,you)==0);
}


//給檔名輸出檔案內容 
void outputfile(string fname){
	
	int c=0;
	fname = fname + ".txt";
	ifstream in(fname.c_str());
	if(!in){
		cout << "FILE NOT FOUND" << endl;
		return ;
	}
	while(!in.eof()){
		string str;
		getline(in, str);
		cout << str << endl;
	}
	cout << endl;
	in.close();
}


class chicken{
	public :
		int str,dex,hp,full,money;
		string name;
		string bark;
		//chicken->feed 之後選擇要吃的食物 
		void eat(int num){ //num 商品編號 
			//for feed
			
			ifstream IN("med_plus.txt");
			int i,buf[5];
			for(i = 0 ; i < num*5 ; i++){
				IN >> buf[i%5];
			}
			if(money + buf[0] < 0){
				cout << "You don't have enough money, plz train to get some.";
			}
			else{
				//cout << buf[0] << " "<<buf[1]<< " "<<buf[2] <<" "<< buf[3] << endl;
				money += buf[0];
				hp += buf[1];
				str += buf[2];
				dex += buf[3];
				full += buf[4];
			}
		}
		//列印食物列表 
		void feed(){
			outputfile("medicine");
			
			char opt;
			cout << "Plz choose one to eat(0 to exit): " << endl;
			cin >> opt;
			if(opt >= '1' && opt <= '9'){
				eat(opt-'0');
			}
			else if(opt == 0)
				return ;
			
		}
		void about(){
						
			cout << "HP   : " << hp <<endl;
			cout << "STR  : " << str<<endl;
			cout << "DEX  : " << dex <<endl;
			cout << "FULL : " << full<<endl;
			cout << "$    : " << money <<endl;
		}
		void save(){
			string fn = "CHICKEN_" + name + ".txt";
			ofstream out(fn.c_str(), ios::out);
			out << hp <<endl;
			out << str<<endl;
			out << dex <<endl;
			out << full<<endl;
			out << money <<endl;			
			out.close();
		}
		virtual int attack(chicken* a){
			cout << name << " hits " << a->name << " " << str << " damages. "<<endl; 
			return str;
		}
};

class str_chicken:public chicken{
	public:
		int attack(chicken* enemy){
			cout << name << " hits " << enemy->name << " " << str*1.5 << " damages. "<<endl; 
			return str*1.5;
		}
};
class hp_chicken:public chicken{
	public:
		int attack(chicken* enemy){
			int dice;
			dice = rand()%2;
			if(dice){
				cout << name << " heals itself "<< hp*0.3 << " hp. "<<endl;
				return str;
			}
			else{
				cout << name << " hits " << enemy->name << " " << str << " damages. "<<endl; 
				return str;
			}
		}
};
class dex_chicken:public chicken{
	public:
		int attack(chicken* enemy){
			int dice;
			dice = rand()%dex;
			if(dice > enemy->dex){
				cout << name << " critical hit "<< enemy->name << " " << str * 2 + dex * 0.1 << " hp. "<<endl;
				return str * 2 + dex * 0.1 ;
			}
			else{
				cout << name << " hits " << enemy->name << " " << str << " damages. "<<endl; 
				return str;
			}
		}
	
};
chicken* load(string fn){
	int o,p,q,r,s;
	string NAME =fn;
	fn = "CHICKEN_" + fn + ".txt";
	ifstream IN(fn.c_str());
	if(!IN){
		cout << "Can't find this chicken. " << endl;
		return NULL; 
	}
	IN >> o >> p >> q >> r >> s ;
	
	
	cout << "A ";;
	chicken *a ;
	
	//chicken 有三種升級型態 各有不同的攻擊技能 
	
	if(o > 300){
		cout << "HP CHICKEN IS LOADED" << endl;
		a = new hp_chicken;
	}
	else if(p > 100){
		cout << "STR CHICKEN IS LOADED" << endl;
		a = new str_chicken;
	}
	else if(q > 100){
		cout << "DEX CHICKEN IS LOADED" << endl;
		a = new dex_chicken;
	}
	else{
		cout << "NORMAL CHICKEN IS LOADED" << endl;
		a = new chicken;
	}
	a->name = NAME;

	a->hp = o;
	a->str = p;
	a->dex = q;
	a->full = r;
	a->money = s;
	
	
	IN.close();
	
	return a;
}
void Combat(){
	cout << "Enter two chicken name" << endl;
	chicken *a;
	chicken *b;
	string str;
	cin >> str;
	a = load(str);
	cin >> str;
	b = load(str);
	
	if( a == NULL || b == NULL){
		cout << "Wrong name plz retry." << endl;
		return ;
	} 
	int A,B;
	A = a->hp;
	B = b->hp;
	
	cout << "--------------------------------------------" << endl;
	a->about();	
	cout << "--------------------------------------------" << endl;
	b->about();
	int c= 1;
	while(1){
		int r,s;
		cout << "Round " << c << endl << endl;
		r = a->attack(b);
		s = b->attack(a);
		
		A-=s;
		B-=r;
		if(A <= 0 && B > 0){
			cout << b->name <<" wins." << endl; 
			break;
		}
		else if(A > 0 && B <= 0){
			cout << a->name <<" wins." << endl; 
			break;
		}
		else if(A <= 0 && B <= 0){
			cout << "Even. What a coincidence!!!" << endl;
		}
		else{
			cout << a->name << " remains " << A << " hp" << endl;
			cout << b->name << " remains " << B << " hp" << endl;
		}
		c++;
		system("pause");
	}
}

void Train(chicken * Q){
	cout << "In train you will play PaperScissorsStone with computer if you win you will get some money" << endl;
	cout << "Each train will cost 10 full" << endl;
	char opt = 'y';
	while(Q->full > 10 && opt == 'y'){
		Q->money += RPS();
		Q->full -= 10;
		cout << "Do you want to continue (y/n)? " ;
		cin >> opt;
	}
	if(Q->full <= 10)
		cout << Q->name << " is tired" <<endl; 
} 
void PLAY(chicken * Q){
	
	char opt;
	while(1){
		outputfile("Play");
		cin >> opt;
		switch(opt){
			case 'a':
				cout<<"        ⊿───\\\\ "<<endl;
				cout<<"    /             \\ "<<endl;
				cout<<"   /   ●    ●〞  \\ "<<endl;
				cout<<"  |                 \\ "<<endl;
				cout<<"  | 	   █▆      |"<<endl;
				cout<<"  /  \\\\\\\\   ▆  \\\\\\\\ \\ " <<endl;
				cout<<" |      	      |"<<endl;
				cout<<" /√               √ /  "<<endl;
				cout<<" \\                   |  "<<endl;
				cout<<"  ▉▃         ▁▉▄/"<<endl;
				Q->about();
				break;
			case 't':
				Train(Q);
				break;
			case 'f':
				Q->feed();
				break;
			case 'c':
				Combat();
				break;
			case 'q':
				Q->save();
				return;
			default:
				break;
		}
		
	}

}

void Create(){
	string name;
	cout << "Please enter chicken name: ";
	cin >> name;
	
	string fn = "CHICKEN_" + name + ".txt";
	ofstream out(fn.c_str(), ios::out);
	out << 100 <<endl;
	out << 25<<endl;
	out << 25 <<endl;
	out << 100<<endl;
	out << 1000 <<endl;				
	out.close();
}

int main(){
	
	srand(time(NULL));
	char opt;
	int flag = 1;

	while(1){
		outputfile("Menu");
		cin >> opt;
		string str;
		chicken *test;
		switch(opt){
			case 'p':

				cout << "Enter the name of chicken: " ;
				cin >> str;
				
				test = load(str);
				if(!test)
					break;
				PLAY(test);
				break;

			case 'c':
				outputfile("Create");
				Create();
				break;
			case 'w':
				Combat();
				break; 
			case 'e':
				outputfile("Bye");
				return 0;
				break;
			default:
				break;
		}
	}
} 
