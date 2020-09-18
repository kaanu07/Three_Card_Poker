#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define mp make_pair
#define pb push_back
#define fi first
#define se second

ll min_amt;
vector<string>value={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
vector<string>suits={"hearts","Spades","Diamonds","clubs"};

vector<pair<string,string>>original_deck;

struct person
{
	string name;
	ll cash;
	vector<pair<int,int>>cards;
	char status;
	person()
	{
		cin>>name;
		cin>>cash;
	}
};


void chaal(person &p,ll &cs,ll &pot)
{
	ll ch;
	while(5>4)
	{
		cout<<"Enter the amt from "<<cs*2<<" to "<<cs*4<<endl;
		cin>>ch;
		if((ch>=cs*2 && ch<=cs*4) || ch>=p.cash)
		{
			p.cash-=ch;
			pot+=ch;

			if(ch>cs)
				cs=ch;
			break;
		}
	}
}

vector<pair<pair<int,string>,int>> winner(vector<person> &players)
{
	vector<pair<pair<int,string>,int>>v;
	for(ll i=0;i<players.size();i++)
	{
		if(players[i].status=='F')
			continue;
		if(players[i].cards[0].se==players[i].cards[1].se && players[i].cards[1].se==players[i].cards[2].se) // Number triplet
		{
			if(players[i].cards[0].se==0)
			{
				v.pb(mp(mp(6,"z"),i));
			}
			else if(players[i].cards[0].se==12)
			{
				v.pb(mp(mp(6,"k"),i));
			}
			else if(players[i].cards[0].se==9)
			{
				v.pb(mp(mp(6,"A"),i));
			}
			else
			{
				v.pb(mp(mp(6,value[players[i].cards[0].se]),i));
			}
			continue;
		}
		vector<ll>cn;
		cn.pb(players[i].cards[0].se);
		cn.pb(players[i].cards[1].se);
		cn.pb(players[i].cards[2].se);
		ll f=4;
		if(players[i].cards[0].fi==players[i].cards[1].fi && players[i].cards[2].fi==players[i].cards[1].fi)
			f=5;

		sort(cn.begin(),cn.end());

		if(cn[0]==cn[1]-1 && cn[1]==cn[2]-1)// trail of same colour and different colour
		{
			if(cn[0]==0)
			{
				v.pb(mp(mp(f,"z"),i));
			}
			else if(cn[0]==0 && cn[1]==11 && cn[2]==12)
			{
				v.pb(mp(mp(f,"y"),i));
			}
			else if(cn[0]==12)
			{
				v.pb(mp(mp(f,"k"),i));
			}
			else if(cn[0]==9)
			{
				v.pb(mp(mp(f,"A"),i));
			}
			else
			{
				v.pb(mp(mp(f,value[players[i].cards[0].se]),i));
			}
			continue;
		}

		if(f==5) // Same colour cards
		{
			f=3;
			string g="";
			for(int lk=0;lk<3;lk++)
			{
				if(cn[lk]==0)
					g+='z';
				else if(cn[lk]==12)
					g+='k';
				else if(cn[lk]==9)
					g+='A';
				else
					g+=value[cn[lk]];
			}
			sort(g.begin(),g.end());
			reverse(g.begin(),g.end());
			v.pb(mp(mp(f,g),i));
			continue;
		}

		if(cn[0]==cn[1]) // Pair
		{
			string g="";
			if(cn[0]==0)
				g+='z';
			else if(cn[0]==12)
				g+='k';
			else if(cn[0]==9)
				g+='A';
			else
				g+=value[cn[0]];
			if(cn[2]==0)
				g+='z';
			else if(cn[2]==12)
				g+='k';
			else if(cn[2]==9)
				g+='A';
			else
				g+=value[cn[2]];
			v.pb(mp(mp(2,g),i));
			continue;
		}

		if(cn[1]==cn[2]) // Pair
		{
			string g="";
			if(cn[1]==0)
				g+='z';
			else if(cn[1]==12)
				g+='k';
			else if(cn[1]==9)
				g+='A';
			else
				g+=value[cn[1]];
			if(cn[0]==0)
				g+='z';
			else if(cn[0]==12)
				g+='k';
			else if(cn[0]==9)
				g+='A';
			else
				g+=value[cn[0]];
			v.pb(mp(mp(2,g),i));
			continue;
		}

		string g="";
		for(int lk=0;lk<3;lk++)  // Distinct cards
			{
				if(cn[lk]==0)
					g+='z';
				else if(cn[lk]==12)
					g+='k';
				else if(cn[lk]==9)
					g+='A';
				else
					g+=value[cn[lk]];
			}
			sort(g.begin(),g.end());
			reverse(g.begin(),g.end());
			v.pb(mp(mp(1,g),i));
	}

	return v;
}
void rounds(vector<person> &players)
{
	int tp=players.size();
	ll cs=min_amt;
	ll pot=0;

	for(ll i=0;i<players.size();i++)
	{
		players[i].cash-=min_amt;
	}

	pot=players.size()*cs;
	ll i=-1;
	ll lucky=tp; // no of folded players
	while(tp>0)
	{
		cout<<"Pot is: "<<pot<<endl;
		i++;
		i=i%players.size();
		if(players[i].status=='F')
			continue;
		if(lucky==1)
		{
			cout<<"Winner of the round is "<<players[i].name<<endl;
			players[i].cash+=pot;
			return;
		}
		cout<<"Turn for player "<<players[i].name<<endl;
		if(players[i].status=='B')
		{
			cout<<"Press 'B' for blind \n Press 'C' to see your cards"<<endl;
			char y;
			cin>>y;
			if(y=='b' || y=='B')
			{
				//blind(players[i],cs);
				ll ch;
				while(5>4)
				{
					cout<<"Enter the amt from "<<min(cs,players[i].cash)<<" to "<<max(players[i].cash,cs)<<endl;
					cin>>ch;
					if(ch>=min(cs,players[i].cash) && ch<=max(cs,players[i].cash))
					{
						players[i].cash-=ch;
						pot+=ch;
						if(ch>cs)
							cs=ch;
						break;
					}
				}
			}
			else if(y=='c' || y=='C')
			{
				cout<<"Your cards are :"<<endl;
				for(ll j=0;j<3;j++)
				{
					cout<<suits[players[i].cards[j].fi]<<"  "<<value[players[i].cards[j].se]<<endl;
				}
				players[i].status='S';
				
				char y2;
				while(5>4)
				{
					cout<<"Press 'C' for chaal or press 'F' to fold your cards"<<endl;
					cin>>y2;
					if(y2=='c' || y2=='C')
					{
						chaal(players[i],cs,pot);
						break;
					}
					else if(y2=='F' || y2=='f')
					{
						players[i].status='F';
						lucky--;
						tp--;
						break;
					}
					else
					{
						cout<<"Enter valid option"<<endl;
					}
				}
			}
			else
			{
				cout<<"Enter valid option"<<endl;
				i--;
				continue;
			}
		}
		else
		{
			char y;
			while(5>4)
			{
			cout<<"Press 'C' for chaal \n Press 'S' to demand show \n Press 'F' to fold your cards"<<endl;
			cin>>y;
				if(y=='c' || y=='C')
				{
					chaal(players[i],cs,pot);
					break;

				}
				else if(y=='F' || y=='f')
				{
					players[i].status='F';
					lucky--;
					tp--;
					break;
				}
				else if(y=='S' || y=='s')
				{
					chaal(players[i],cs,pot);
					players[i].status='C';
					tp--;
					break;
				}
			}
		}
	}
	vector<pair<pair<int,string>,int>>v=winner(players);
	sort(v.begin(),v.end());
	ll w=v[v.size()-1].se;
	players[w].cash+=pot;
	cout<<"Winner of the round is "<<players[w].name<<endl;
}

int main()
{
	map<string,int>card_dictionary;
	card_dictionary["A"]=0;
	card_dictionary["2"]=1;
	card_dictionary["3"]=2;
	card_dictionary["4"]=3;
	card_dictionary["5"]=4;
	card_dictionary["6"]=5;
	card_dictionary["7"]=6;
	card_dictionary["8"]=7;
	card_dictionary["9"]=8;
	card_dictionary["10"]=9;
	card_dictionary["J"]=10;
	card_dictionary["K"]=12;

	card_dictionary["hearts"]=0;
	card_dictionary["Spades"]=1;
	card_dictionary["Diamonds"]=2;
	card_dictionary["clubs"]=3;
	
	cout<<"Enter the number of players"<<endl;
	ll pn;
	cin>>pn;
	vector<person>players;

	for(ll i=0;i<pn;i++)
	{
	 	cout<<"Enter the name and amount of player "<<i+1<<endl;
	 	players.pb(person());
	}

	cout<<"Enter the minimum amount"<<endl;
	cin>>min_amt;

	for(ll i=0;i<5;i++)
	{
		original_deck.clear();
		
		for(ll i=0;i<4;i++)
		{
			for(ll j=0;j<13;j++)
			{
				original_deck.pb(mp(suits[i],value[j]));
			}
		}
	
		set<pair<ll,ll>>s;
		for(ll p=0;p<players.size();p++)
		{
			if(players[p].cash<min_amt)
			{
				cout<<"You are removed "<<players[p].name<<endl;
				players.erase(players.begin()+p);
				p--;
				continue;
			}
			else
			{
				cout<<players[p].name<<" has "<<players[p].cash<<endl;
			}
			for(ll no=0;no<3;no++)
			{
				
			srand(time(0));

			ll card_number=rand()%original_deck.size();

			ll x,y;
			cout<<card_dictionary[original_deck[card_number].fi]<<endl;
			x=card_dictionary[original_deck[card_number].fi];
			y=card_dictionary[original_deck[card_number].se];
			original_deck.erase(original_deck.begin()+card_number);
			if(s.count(mp(x,y))>0)
			{
				no--;
				continue;
			}
				s.insert(mp(x,y));
				players[p].cards.pb(mp(x,y));
			}
			players[p].status='B';
		}
		cout<<"Round "<<i+1<<endl;
		if(players.size()==1)
		{
			cout<<"Only one left"<<endl;
			break;
		}
		rounds(players);
	}
	cout<<"ending"<<endl;
}