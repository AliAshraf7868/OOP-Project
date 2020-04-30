#include<iostream>
#include<conio.h>
#include<fstream>
#include<ctime>
using namespace std;
static int check_in=0;
static int check_out=0;
void display_room(int,string room_rec[][5][10],int);
void reserved_room(string room_rec[][5][10]);
void detail_report(string room_rec[][5][10]);
const int floor=6,rooms=251,size=30;
const int flo=5,typ=5,rom=10,size2=262;
class room;
class standard;
class customer_info
{
	private:
		char first_name[size];
		char last_name[size];
		int age;
		char gender[size];
		int id_card_number;
		int balance;
		int total_days_to_reserve;
		int floor_num;
		int room_num;
		int room_type;

	    int day_in,month_in,year_in;
	    int hrs_in,min_in,sec_in;
	    int day_out,month_out,year_out;
	    int hrs_out,min_out,sec_out;
		int rem_hours;
		struct check_room
        {
	      int f_num;
	      int t_of_class;
	      int r_num;	
       };
	public:	
	    customer_info()
		{
			
		}	
		void new_booking(int);
		customer_info check_previous(int,bool&,int);
		void remaining_hours();
		void allot_a_room(int type);
		void display();
		void service_start();
		int get_f_num(){  return(floor_num);  }
		int get_r_type(){  return(room_type);  }
		int get_r_num(){  return(room_num);  }
			
};
void customer_info::service_start()
{
	int in=0;
	customer_info oo;
	int id_card_num;
	cout<<"enter id card number"<<endl;
	cin>>id_card_num;
	ifstream fin;
    fin.open("customer_file.dat");
    ofstream fout;
	fout.open("new_file.dat",ios::binary|ios::out);
    while(fin.read((char*)&oo,sizeof(oo)))
    {
    	if(oo.id_card_number==id_card_num)
    	{
    	 in=1;
    	 cout<<"wellcome "<<"Mr/miss "<<oo.first_name<<" "<<oo.last_name<<endl;
         time_t ttime = time(0);
         tm *local_time = localtime(&ttime);
         oo.day_in= local_time->tm_mday;
	     oo.month_in= 1 + local_time->tm_mon;
	     oo.year_in=(1900 + local_time->tm_year);
	     oo.hrs_in=local_time->tm_hour ;
	     oo.min_in=local_time->tm_min;
	     oo.sec_in=local_time->tm_sec;
	    fout.write((char*)&oo,sizeof(oo));		
		check_in++;	
		cout<<"you have successfully entered"<<endl;	
		}
		else
		 fout.write((char*)&oo,sizeof(oo));
	}
	if(in==0)
	{
		cout<<"sorry sir your information is not save"<<endl;
		cout<<"first reserved a room"<<endl;
		fin.close();
	    fout.close(); 
		remove("new_file.dat");
	}
    else
	{
	fin.close();
	fout.close();  
	remove("customer_file.dat");
	rename("new_file.dat","customer_file.dat");	
    }
	
}
void customer_info::allot_a_room(int type)
{
		cout<<"wellcom Mr/Miss: "<<first_name<<" "<<last_name<<endl;
		cout<<"id card number "<<id_card_number<<endl;
		cout<<"balance "<<balance<<endl;
		cout<<"total day for reserved "<<total_days_to_reserve<<endl;
		put_again1:	cout<<"\nenter floor number: \n";
	    cout<<"1 to 5 :";cin>>floor_num;
        room_type=type;
        cout<<"room number: ";cin>>room_num;cout<<endl;
        check_room see;
        ifstream fin;
        fin.open("reserved_room.dat");
    while(fin.read((char*)&see,sizeof(see)))
    {
    	if(see.f_num==(floor_num-1))
    	{
    		if(see.r_num==(room_num-1)%10)
    		{
    			if(see.t_of_class==room_type)
    			{
    				cout<<"room already reserved"<<endl;
    				cout<<"select other one"<<endl;
    				goto put_again1;
    				
				}
			}
		}
	}
    fin.close();
    
	
	 day_in=0;
	 month_in=0;
	 year_in=0;
     hrs_in=0;
	 min_in=0;
	 sec_in=0;
	
	
	 day_out=0;
	 month_out=0;
	 year_out=0;
     hrs_out=0;
	 min_out=0;
	 sec_out=0;

	 rem_hours=total_days_to_reserve*24;
	if(type==0)
	{
		balance=300;
		balance*=total_days_to_reserve;
	}
		else if(type==1)
	{
		balance=500;
		balance*=total_days_to_reserve;
	}
	else if(type==2)
	{
		balance=1000;
		balance*=total_days_to_reserve;
	}
	else if(type==3)
	{
		balance=2000;
		balance*=total_days_to_reserve;
	}
	else if(type==4)
	{
		balance=5000;
		balance*=total_days_to_reserve;
	}
 	
}
customer_info customer_info::check_previous(int new_id,bool &yes_no,int type)
{

	yes_no=false;
	customer_info oo,oo1;
	cout<<"id"<<new_id<<endl;
	ifstream fin;
   fin.open("customer_file.dat");
   ofstream fout;
   fout.open("new_file.dat",ios::binary|ios::out);
    while(fin.read((char*)&oo,sizeof(oo)))
    {
    	if(oo.id_card_number==new_id)
    	{
    		yes_no=true;
			oo.allot_a_room(type);
			oo1=oo;
			fout.write((char*)&oo,sizeof(oo));
		}
		else
		fout.write((char*)&oo,sizeof(oo));
		
		
	}

	fin.close();
	fout.close();
	remove("customer_file.dat");
	rename("new_file.dat","customer_file.dat");	
	return(oo1);
}
void customer_info::display()
{
		cout<<first_name<<" "<<last_name<<endl;
		cout<<"age"<<age<<" "<<gender<<endl;
		cout<<"id card number "<<id_card_number<<endl;
		cout<<"balance "<<balance<<endl;
		cout<<"total day for reserved "<<total_days_to_reserve<<endl;
		cout<<"floor number "<<floor_num<<endl;
		cout<<"room type ";
		if(room_type==0)
		cout<<"standard"<<endl;
		else if(room_type==1)
		cout<<"Moderate"<<endl;
		else if(room_type==2)
		cout<<"superior"<<endl;
		else if(room_type==3)
		cout<<"Junior suite"<<endl;
		else if(room_type==4)
		cout<<"suite"<<endl;
		cout<<"room number "<<room_num<<endl;
		cout<<"day: "<<day_in<<"/"<<month_in<<"/"<<year_in<<endl;
	    cout<<"time: "<<hrs_in<<"/"<<min_in<<"/"<<sec_in<<endl;
		cout<<"rem hours "<<rem_hours;
	
	
}
void customer_info::new_booking(int type)
{
	
	cout<<"enter first name: ";cin>>first_name;
	cout<<"\nenter last name: ";cin>>last_name;
	cout<<"\nage: ";cin>>age;	
	cout<<"\nid card number";cin>>id_card_number;
	cout<<"\ngender:   MALE OR FEMALE ";cin>>gender;
	cout<<"\ntotal day to reserve: ";cin>>total_days_to_reserve;
put_again:	cout<<"\nenter floor number: \n";
	cout<<"1 to 5 :";cin>>floor_num;
    room_type=type;
    cout<<"room number: ";cin>>room_num;cout<<endl;
    check_room see;
    ifstream fin;
    fin.open("reserved_room.dat");
    while(fin.read((char*)&see,sizeof(see)))
    {
    	if(see.f_num==(floor_num-1))
    	{
    		if(see.r_num==(room_num-1)%10)
    		{
    			if(see.t_of_class==room_type)
    			{
    				cout<<"room already reserved"<<endl;
    				cout<<"select other one"<<endl;
    				goto put_again;
				}
			}
		}
	}
    fin.close();
	 day_in=0;
	 month_in=0;
	 year_in=0;
     hrs_in=0;
	 min_in=0;
	 sec_in=0;
	 
	  day_out=0;
	 month_out=0;
	 year_out=0;
	 
     hrs_out=0;
	 min_out=0;
	 sec_out=0;

	 rem_hours=total_days_to_reserve*24;
	if(type==0)
	{
		balance=300;
		balance*=total_days_to_reserve;
	}
	else if(type==1)
	{
		balance=500;
		balance*=total_days_to_reserve;
	}
	else if(type==2)
	{
		balance=1000;
		balance*=total_days_to_reserve;
	}
	else if(type==3)
	{
		balance=2000;
		balance*=total_days_to_reserve;
	}
	else if(type==4)
	{
		balance=5000;
		balance*=total_days_to_reserve;
	}
}
void customer_info::remaining_hours()
{
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
	customer_info read_obj;
	ifstream fin;
	ofstream fout;
	fin.open("customer_file.dat",ios::binary);
	fout.open("new_file.dat",ios::binary|ios::out);
	while(fin.read((char*)&read_obj,sizeof(read_obj)))
	{
		
		if(read_obj.hrs_in>0)
		{
			if(local_time->tm_mday==read_obj.day_in)
			{
				if(local_time->tm_hour>read_obj.hrs_in)
				{
					read_obj.rem_hours-=local_time->tm_hour-read_obj.hrs_in;
					if(read_obj.rem_hours<=0)
					{
					   read_obj.rem_hours=0;
					   time_t ttime = time(0);
                       tm *local_time = localtime(&ttime);
                       read_obj.day_out= local_time->tm_mday;
	                   read_obj.month_out= 1 + local_time->tm_mon;
	                   read_obj.year_out=(1900 + local_time->tm_year);
	                   read_obj.hrs_out=local_time->tm_hour ;
	                   read_obj.min_out=local_time->tm_min;
	                   read_obj.sec_out=local_time->tm_sec;
                        check_room see;
                        ifstream fin2;
                        ofstream fout2;
                        fin2.open("reserved_room.dat");
                        fout2.open("res.dat",ios::binary|ios::out);
                        while(fin2.read((char*)&see,sizeof(see)))
                        {
    	                      if(see.f_num==(read_obj.floor_num-1))
    	                       {
    		                    if(see.r_num==(read_obj.room_num-1)%10)
    		                    {
    			                if(see.t_of_class==read_obj.room_type)
    			               {
    			               	
    				         
				               }
				               else
		                       fout2.write((char*)&see,sizeof(see));
			                   }
			                   else
		                       fout2.write((char*)&see,sizeof(see));
		                       }
		                       else
		                       fout2.write((char*)&see,sizeof(see));
	                    }
	                    fout2.close();
                        fin2.close();
                        remove("reserved_room.dat");
                        rename("res.dat","reserved_room.dat");
	                   check_out++;
	                   
	                   
					   	
					}
				}
				else if(local_time->tm_hour<read_obj.hrs_in)
				{
					int a=0;
					a=24-read_obj.hrs_in;
					a+=local_time->tm_hour;
					read_obj.rem_hours-=a;
					if(read_obj.rem_hours<=0)
					{
					  read_obj.rem_hours=0;
					   time_t ttime = time(0);
                       tm *local_time = localtime(&ttime);
                       read_obj.day_out= local_time->tm_mday;
	                   read_obj.month_out= 1 + local_time->tm_mon;
	                   read_obj.year_out=(1900 + local_time->tm_year);
	                   read_obj.hrs_out=local_time->tm_hour ;
	                   read_obj.min_out=local_time->tm_min;
	                   read_obj.sec_out=local_time->tm_sec;
                        check_room see;
                        ifstream fin3;
                        ofstream fout3;
                        fin3.open("reserved_room.dat");
                        fout3.open("res.dat",ios::binary|ios::out);
                        while(fin3.read((char*)&see,sizeof(see)))
                        {
    	                      if(see.f_num==(read_obj.floor_num-1))
    	                       {
    		                    if(see.r_num==(read_obj.room_num-1)%10)
    		                    {
    			                if(see.t_of_class==read_obj.room_type)
    			               {
    			               	
    				         
				               }
				               else
		                       fout3.write((char*)&see,sizeof(see));
			                   }
			                   else
		                       fout3.write((char*)&see,sizeof(see));
		                       }
		                       else
		                       fout3.write((char*)&see,sizeof(see));
	                    }
	                    fout3.close();
                        fin3.close();
                        remove("reserved_room.dat");
                        rename("res.dat","reserved_room.dat");
						check_out++;	
					}
				   }		
		          }	
		         
				 else if(local_time->tm_mday>read_obj.day_in)
			{
				int a;
				a=local_time->tm_mday-read_obj.day_in;
				a*=24;
				read_obj.rem_hours-=a;
				if(read_obj.rem_hours<=0)
					{
					  read_obj.rem_hours=0;
					   time_t ttime = time(0);
                       tm *local_time = localtime(&ttime);
                       read_obj.day_out= local_time->tm_mday;
	                   read_obj.month_out= 1 + local_time->tm_mon;
	                   read_obj.year_out=(1900 + local_time->tm_year);
	                   read_obj.hrs_out=local_time->tm_hour ;
	                   read_obj.min_out=local_time->tm_min;
	                   read_obj.sec_out=local_time->tm_sec;
                        check_room see;
                        ifstream fin4;
                        ofstream fout4;
                        fin4.open("reserved_room.dat");
                        fout4.open("res.dat",ios::binary|ios::out);
                        while(fin4.read((char*)&see,sizeof(see)))
                        {
    	                      if(see.f_num==(read_obj.floor_num-1))
    	                       {
    		                    if(see.r_num==(read_obj.room_num-1)%10)
    		                    {
    			                if(see.t_of_class==read_obj.room_type)
    			               {
    			               	
    				         
				               }
				               else
		                       fout4.write((char*)&see,sizeof(see));
			                   }
			                   else
		                       fout4.write((char*)&see,sizeof(see));
		                       }
		                       else
		                       fout4.write((char*)&see,sizeof(see));
	                    }
	                    fout4.close();
                        fin4.close();
                        remove("reserved_room.dat");
                        rename("res.dat","reserved_room.dat");
					}
			}
			else if(local_time->tm_mday<read_obj.day_in)
			{
				int a;
				a=30-read_obj.day_in;
				a+=local_time->tm_mday;
				a*=24;
				read_obj.rem_hours-=a;
				if(read_obj.rem_hours<=0)
					{
					  read_obj.rem_hours=0;
					   time_t ttime = time(0);
                       tm *local_time = localtime(&ttime);
                       read_obj.day_out= local_time->tm_mday;
	                   read_obj.month_out= 1 + local_time->tm_mon;
	                   read_obj.year_out=(1900 + local_time->tm_year);
	                   read_obj.hrs_out=local_time->tm_hour ;
	                   read_obj.min_out=local_time->tm_min;
	                   read_obj.sec_out=local_time->tm_sec;
                        check_room see;
                        ifstream fin5;
                        ofstream fout5;
                        fin5.open("reserved_room.dat");
                        fout5.open("res.dat",ios::binary|ios::out);
                        while(fin5.read((char*)&see,sizeof(see)))
                        {
    	                      if(see.f_num==(read_obj.floor_num-1))
    	                       {
    		                    if(see.r_num==(read_obj.room_num-1)%10)
    		                    {
    			                if(see.t_of_class==read_obj.room_type)
    			               {
    			               	
    				         
				               }
				               else
		                       fout5.write((char*)&see,sizeof(see));
			                   }
			                   else
		                       fout5.write((char*)&see,sizeof(see));
		                       }
		                       else
		                       fout5.write((char*)&see,sizeof(see));
	                    }
	                    fout5.close();
                        fin5.close();
                        remove("reserved_room.dat");
                        rename("res.dat","reserved_room.dat");
						check_out++;	
					}
				
				
			} 
	}

		
	
	fout.write((char*)&read_obj,sizeof(read_obj));
	
}
    fin.close();
	fout.close();
	remove("customer_file.dat");
	rename("new_file.dat","customer_file.dat");	
}

class room
{
	private:
		struct reserved
        {
	      int f_num;
	      int t_of_class;
	      int r_num;	
       };
	protected:
		customer_info *customer,customer1;
	public:
		room(){	 customer=new customer_info();   }
		virtual void reserved_a_room()=0;
		void allocate(string [][5][10]);
		void start_system(string [][5][10]);
		int get_f_num(){  return(customer->get_f_num());  }
		int get_r_type(){ return(customer->get_r_type()); }
		int get_r_num(){  return(customer->get_r_num());  }
};

void room::start_system(string record[][5][10])
{
		reserved obj;
		ifstream fin;
		fin.open("reserved_room.dat");
		while(fin.read((char*)&obj,sizeof(obj)))
		{
		record[obj.f_num][obj.t_of_class][obj.r_num]=" X  ";
		}
		fin.close();
	
}
void room::allocate(string record[][5][10])
{

	reserved obj;
	obj.f_num=customer1.get_f_num();
	obj.t_of_class=customer1.get_r_type();
	obj.r_num=customer1.get_r_num();
	obj.f_num-=1;
	obj.r_num-=1;
	obj.r_num%=10;
	ofstream fout;
	fout.open("reserved_room.dat",ios::binary|ios::out|ios::app);
	fout.write((char*)&obj,sizeof(obj));
	fout.close();
	record[obj.f_num][obj.t_of_class][obj.r_num]=" X  ";

}
class standard:public room
{
	private:
		
    public:
    	standard():room()
    	{
		}
    	void reserved_a_room();	
}; 
void standard::reserved_a_room()
{

	string decider;
	cout<<"Are you old customer"<<endl;
	cout<<"Yes\tNo"<<endl;
	cin>>decider;
	if(decider=="yes"||decider=="Yes"||decider=="YES")
	{
		int id,address=0;
		cout<<"enter id card number"<<endl;
		cin>>id;	
		bool yes_no=false;
		customer1=customer->check_previous(id,yes_no,0);
	
		if(yes_no==true)
		{
		cout<<"thankou sir"<<endl;	
		}
	    else
		{
			cout<<"sorry your record was not found"<<endl;
			cout<<"enter new"<<endl;
			customer1.new_booking(0);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
		}
	}
	else if(decider=="no"||decider=="No"||decider=="NO")
	{
			customer1.new_booking(0);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
	}	
}



class moderate:public room
{
	private:
		
    public:
    	moderate():room()
    	{
		}
    	void reserved_a_room();	
}; 
void moderate::reserved_a_room()
{

	string decider;
	cout<<"Are you old customer"<<endl;
	cout<<"Yes\tNo"<<endl;
	cin>>decider;
	if(decider=="yes"||decider=="Yes"||decider=="YES")
	{
		int id,address=0;
		cout<<"enter id card number"<<endl;
		cin>>id;	
		bool yes_no=false;
			customer1=customer->check_previous(id,yes_no,1);
		if(yes_no==true)
		{
			
			cout<<"thankou sir"<<endl;
		}
	    else
		{
			cout<<"sorry your record was not found"<<endl;
			cout<<"enter new"<<endl;
			customer1.new_booking(1);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
		}
	}
	else if(decider=="no"||decider=="No"||decider=="NO")
	{
			customer1.new_booking(1);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
	}	
	
}




class superior:public room
{
	private:
		
    public:
    	superior():room()
    	{
		}
    	void reserved_a_room();	
}; 
void superior::reserved_a_room()
{

	string decider;
	cout<<"Are you old customer"<<endl;
	cout<<"Yes\tNo"<<endl;
	cin>>decider;
	if(decider=="yes"||decider=="Yes"||decider=="YES")
	{
		int id,address=0;
		cout<<"enter id card number"<<endl;
		cin>>id;	
		bool yes_no=false;
			customer1=customer->check_previous(id,yes_no,2);
	
		if(yes_no==true)
		{
			
		cout<<"thankou sir"<<endl;	
		}
	    else
		{
			cout<<"sorry your record was not found"<<endl;
			cout<<"enter new"<<endl;
			customer1.new_booking(2);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
		}
	}
	else if(decider=="no"||decider=="No"||decider=="NO")
	{
			customer1.new_booking(2);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
	}	
	
}


class junior_suite:public room
{
	private:
		
    public:
    	junior_suite():room()
    	{
		}
    	void reserved_a_room();	
}; 
void junior_suite::reserved_a_room()
{

	string decider;
	cout<<"\nAre you old customer"<<endl;
	cout<<"Yes\tNo"<<endl;
	cin>>decider;
	if(decider=="yes"||decider=="Yes"||decider=="YES")
	{
		int id,address=0;
		cout<<"enter id card number"<<endl;
		cin>>id;	
		bool yes_no=false;
		customer1=customer->check_previous(id,yes_no,3);
	
		if(yes_no==true)
		{
			
		 cout<<"thankou sir"<<endl;
		}
	    else
		{
			cout<<"sorry your record was not found"<<endl;
			cout<<"enter new"<<endl;
			customer1.new_booking(3);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
		}
	}
	else if(decider=="no"||decider=="No"||decider=="NO")
	{
			customer1.new_booking(3);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
	}	
	
}


class suite:public room
{
	private:
		
    public:
    	suite():room()
    	{
		}
    	void reserved_a_room();	
}; 
void suite::reserved_a_room()
{

	string decider;
	cout<<"\nAre you old customer"<<endl;
	cout<<"Yes\tNo"<<endl;
	cin>>decider;
	if(decider=="yes"||decider=="Yes"||decider=="YES")
	{
		int id,address=0;
		cout<<"enter id card number"<<endl;
		cin>>id;	
		bool yes_no=false;
		customer1=customer->check_previous(id,yes_no,3);
	
		if(yes_no==true)
		{
			
		 cout<<"thankou sir"<<endl;	
		}
	    else
		{
			cout<<"sorry your record was not found"<<endl;
			cout<<"enter new"<<endl;
			customer1.new_booking(4);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
		}
	}
	else if(decider=="no"||decider=="No"||decider=="NO")
	{
			customer1.new_booking(4);
			ofstream fout;
			fout.open("customer_file.dat",ios::binary|ios::app);
			fout.write((char*)&customer1,sizeof(customer1));
			fout.close();
	}	
	
}


main()
{  
    room *re_fill=new standard();
    customer_info reset;
	int counter[262],h;
	for(int i=0;i<250;i++)
	counter[i]=i+1;	
	string decider[]={"st","nd","rd","th","th"};
	string room_record[5][5][10];
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			for(int k=0;k<10;k++)
			{
				room_record[i][j][k]="free";
			}
		}
	}
	reset.remaining_hours();
	re_fill->start_system(room_record);

do{
	int operation=0;
	room *manage;
	customer_info obj;
	customer_info oo,oo1;
	ofstream wr;
	ifstream read;
	system("cls");
	cout<<"\n[ *************** HOTEL MANAGEMENT SYSTEM -> MENU *************** ]"<<endl;
	cout<<"\npress 1 to reserved a room "<<endl;
	cout<<"press 2 to checkin customer/visitor"<<endl;
	cout<<"press 3 to view reserved rooms "<<endl;
	cout<<"press 4 to to see detail report "<<endl;
	cout<<"press 5 to exit "<<endl;
	cin>>operation;
	if(operation==1)
	{
		
	int type;
	system("cls");
	cout<<"select room type"<<endl;
	cout<<"1 for standard"<<endl;
	cout<<"2 for moderate"<<endl;
	cout<<"3 for superior"<<endl;
	cout<<"4 for junior suite"<<endl;
	cout<<"5 for suite"<<endl;
	cin>>type;
	if(type==1)
	{
	    display_room(h=0,room_record,0);						
		manage=new standard();
		manage->reserved_a_room();
		getch();
		manage->allocate(room_record);			
  }		  
  else if(type==2)
  {
  	    display_room(h=10,room_record,1);						
		manage=new moderate();
		manage->reserved_a_room();
		getch();
		manage->allocate(room_record);			 	
  }
  else if(type==3)
  {
  	    display_room(h=20,room_record,2);						
		manage=new superior();
		manage->reserved_a_room();
		getch();
		manage->allocate(room_record);		 	
  }
  else if(type==4)
  {
  	    display_room(h=30,room_record,3);						
		manage=new junior_suite();
		manage->reserved_a_room();
		getch();
		manage->allocate(room_record);			  	
  }
  else if(type==5)
  {
  	    display_room(h=40,room_record,4);						
		manage=new suite();
		manage->reserved_a_room();
		getch();
		manage->allocate(room_record);				
  }
  
 }
 else if(operation==2)
 {
 	customer_info check_in;
 	check_in.service_start();
	 getch();	
 }
 else if(operation==3)
 {
 	system("cls");
 	reserved_room(room_record);
 	getch();
 }
 else if(operation==4)
 {
 	detail_report(room_record);
 	getch();
 }
 /*ofstream fout;int a=1;
 
 fout.open("customer_file.dat",ios::binary|ios::out|ios::app);
 while(a<2){
 oo.new_booking(0);	
 fout.write((char*)&oo,sizeof(oo));
 a++;
}
  fout.close();	*/
   ifstream fin;
   fin.open("customer_file.dat");
    while(fin.read((char*)&oo,sizeof(oo)))
    {  	
    oo.display();
	}
    fin.close();
    getch();

}while(1);

}



void display_room(int h,string room_rec[][5][10],int j)
{
	int counter[262],j1=j,j2=j;j2++;
	for(int i=0;i<250;i++)
	counter[i]=i+1;	
	string decider[]={"st","nd","rd","th","th"};
	
		for(int i=0;i<5;i++)
	    {
		cout<<endl;
		for(int p=0;p<44;p++){cout<<" ";}
		cout<<i+1<<decider[i]<<" floor";
		for(int p=0;p<45;p++){cout<<" ";}
		cout<<endl;
		for(j1=j;j1<j2;j1++)
		{
			for(int p=0;p<100;p++){cout<<"_";}
			cout<<endl;
			for(int k=0;k<10;k++)
			{
				if(h<10)
				cout<<counter[h]<<"   "<<room_rec[i][j][k]<<" |";
				else if(h<100)
				cout<<counter[h]<<"  "<<room_rec[i][j][k]<<" |";
				else
				cout<<counter[h]<<" "<<room_rec[i][j][k]<<" |";
			
				
				h++;
			}
			cout<<endl;
			h+=40;
		}
   }	
}


void reserved_room(string room_rec[][5][10])
{
	int counter[262],h;
	for(int i=0;i<250;i++)
	counter[i]=i+1;	
	string decider[]={"st","nd","rd","th","th"};
	h=0;
	for(int i=0;i<5;i++)
	{
		cout<<endl<<endl;
		for(int p=0;p<44;p++){cout<<" ";}
		cout<<i+1<<decider[i]<<" floor";
		for(int p=0;p<45;p++){cout<<" ";}
		cout<<endl;

		for(int j=0;j<5;j++)
		{
			for(int p=0;p<100;p++){cout<<"_";}
			cout<<endl;
			for(int k=0;k<10;k++)
			{
				if(h<10)
				cout<<counter[h]<<"   "<<room_rec[i][j][k]<<" |";
				else if(h<100)
				cout<<counter[h]<<"  "<<room_rec[i][j][k]<<" |";
				else
				cout<<counter[h]<<" "<<room_rec[i][j][k]<<" |";
			
				
				h++;
			}
			cout<<endl;
		}
	}	
}

void detail_report(string room_rec[][5][10])
{
	
	int counter[262],h,count=0,tell[5];
	for(int i=0;i<250;i++)
	counter[i]=i+1;	
	string decider[]={"st","nd","rd","th","th"};
	h=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			for(int k=0;k<10;k++)
			{
				if(room_rec[i][j][k]==" X  ")
				{
					count++;
				}
			}
		}
	}
	cout<<endl;
	cout<<"the hotel has reserved rooms: "<<count;
	cout<<endl;
	for(int i=0;i<5;i++)
	{
		
		count=0;
        for(int l=0;l<5;l++)
        {
		for(int j=i;j<i+1;j++)
		{
			
		
			for(int k=0;k<10;k++)
			{
				if(room_rec[l][j][k]==" X  ")
				{
					count++;
				}
			
				
				h++;
			}
		}
	}
		tell[i]=count;

	}
		cout<<"standard: "<<"reserved: "<<tell[0]<<" free: "<<50-tell[0]<<endl;
		cout<<"moderate: "<<"reserved: "<<tell[1]<<" free: "<<50-tell[1]<<endl;
		cout<<"superior: "<<"reserved: "<<tell[2]<<" free: "<<50-tell[2]<<endl;
		cout<<"junior suite: "<<"reserved: "<<tell[3]<<" free: "<<50-tell[3]<<endl;
		cout<<"suite: "<<"reserved: "<<tell[4]<<" free: "<<50-tell[4]<<endl;
		cout<<endl;
		time_t ttime = time(0);
        tm *local_time = localtime(&ttime);
		cout<<"check in "<<local_time->tm_mday<<"/"<<1 + local_time->tm_mon;
		cout<<"/"<<(1900 + local_time->tm_year);
		cout<<" is:"<<check_in<<endl;
		cout<<"check out "<<local_time->tm_mday<<"/"<<1 + local_time->tm_mon;
		cout<<"/"<<(1900 + local_time->tm_year);
		cout<<" is:"<<check_out<<endl;
		 
	
}




