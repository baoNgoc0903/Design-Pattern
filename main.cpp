//#include <iostream>
//using namespace std;
//#include <QList>
//class ISubject;
//class IObserver{
//public:
//    virtual void update(int x, int y, int z) = 0;
//    virtual ISubject* getSubject() = 0;
//};

//class ISubject{
//public:
//    virtual void addObserver(IObserver* ob)    = 0;
//    virtual void removeObserver(IObserver* ob) = 0;
//    virtual void notifyObserver()              = 0;
//};

//class IDisplay{
//public:
//    virtual void display() = 0;
//};


//class WeatherData: public ISubject{
//private:
//    int m_x;
//    int m_y;
//    int m_z;
//    QList<IObserver* > listObserver;
//public:
//    WeatherData(): m_x(0), m_y(0), m_z(0)
//    {}
//    void addObserver(IObserver* ob){
//        listObserver.append(ob);
//        cout << "added" << endl;
//    }
//    void removeObserver(IObserver* ob){
//        int i = listObserver.indexOf(ob);
//        if(i >=0){
//            listObserver.removeAt(i);
//        }
//    }
//    void notifyObserver(){
//        cout << "changed" << endl;
//        for(int i = 0; i<listObserver.count(); i++){
//            listObserver.at(i)->update(m_x, m_y, m_z);
//        }
//    }
//    void setData(int x, int y, int z){
//        bool check = false;
//        if(m_x !=x){
//            m_x = x;
//            check = true;
//        }
//        if(m_y !=y){
//            m_y = y;
//            check = true;
//        }
//        if(m_z !=z){
//            m_z = z;
//            check = true;
//        }
//        if(check)   notifyObserver();
//    }
//};

//class DisplayOne: public IObserver, public IDisplay{
//private:
//    ISubject* m_sub; // observer tự remove nó khỏi subject khi nó muốn
//public:
//    DisplayOne(ISubject* sub = nullptr){
//        m_sub = sub; // tham chiếu tới subject được đkí bởi observer
//        m_sub->addObserver(this); // đkí
//    }
//    void update(int x, int y, int z){
//        cout << x << " " << y << " " << z << endl;
//        cout << x+y+z << endl;
//        display();
//    }
//    void display(){
//        cout << "updated" << endl;
//    }
//    ISubject* getSubject(){
//        return m_sub; // lấy ra thằng subject đó và remove hay làm gì đó
//    }
//};
//class DisplayTwo: public IObserver, public IDisplay{
//private:
//    ISubject* m_sub;
//public:
//    DisplayTwo(ISubject* sub = nullptr){
//        m_sub = sub;
//        m_sub->addObserver(this);
//    }
//    void update(int x, int y, int z){
//        cout << x << " " << y << " " << z << endl;
//        cout << -x-y-z << endl;
//        display();
//    }
//    void display(){
//        cout << "updated" << endl;
//    }
//    ISubject* getSubject(){
//        return m_sub;
//    }
//};
//int main(int argc, char *argv[])
//{
//    WeatherData* sub = new WeatherData;
//    IObserver* allOb[2];
//    allOb[0] = new DisplayOne(sub);
//    allOb[1] = new DisplayTwo(sub);

//    sub->setData(1,2,3);
//    allOb[0]->getSubject()->removeObserver(allOb[0]);
//    sub->setData(2,2,3);
//    return 0;
//}





























#include <iostream>
using namespace std;
#include <QList>
class ISubject;
class baseISubject;
class IObserver{
public:
    virtual void update(int x, int y, int z) = 0;
    virtual void update(string x, string y, string z) = 0;
    virtual baseISubject* getSubject(baseISubject* sb) = 0;
};
class baseIObserver;
class ISubject{
public:
    virtual void addObserver(baseIObserver* ob)    = 0;
    virtual void removeObserver(baseIObserver* ob) = 0;
    virtual void notifyObserver()              = 0;
};
class baseISubject: public ISubject{
protected:
    QList<baseIObserver* > listObserver;
public:
    baseISubject(){}
    void addObserver(baseIObserver* ob){
        listObserver.append(ob);
        cout << "added" << endl;
    }
    void removeObserver(baseIObserver* ob){
        int i = listObserver.indexOf(ob);
        if(i >=0){
            listObserver.removeAt(i);
        }
    }
    virtual void notifyObserver(){}
};
class baseIObserver: public IObserver{
protected:
    QList<baseISubject* > m_listsub;
public:
    baseIObserver(){}
    virtual void update(int x, int y, int z){}
    virtual void update(string x, string y, string z){}
    void addSubject(baseISubject* sub){
        sub->addObserver(this);
        m_listsub.append(sub);
    }
    virtual baseISubject* getSubject(baseISubject* sb){
        int i = m_listsub.indexOf(sb);
        return m_listsub.at(i);
    }
};

class IDisplay{
public:
    virtual void display() = 0;
};


class WeatherData: public baseISubject{
private:
    int m_x;
    int m_y;
    int m_z;
public:
    WeatherData(): m_x(0), m_y(0), m_z(0){}

    void notifyObserver(){
        cout << "changed" << endl;
        for(int i = 0; i<listObserver.count(); i++){
            listObserver.at(i)->update(m_x, m_y, m_z);
        }
    }
    void setData(int x, int y, int z){
        bool check = false;
        if(m_x !=x){
            m_x = x;
            check = true;
        }
        if(m_y !=y){
            m_y = y;
            check = true;
        }
        if(m_z !=z){
            m_z = z;
            check = true;
        }
        if(check)   notifyObserver();
    }
};
class WeatherDataAgain: public baseISubject{
private:
    string m_x;
    string m_y;
    string m_z;
public:
    WeatherDataAgain(): m_x(""), m_y(""), m_z(""){}

    void notifyObserver(){
        cout << "changed" << endl;
        for(int i = 0; i<listObserver.count(); i++){
            listObserver.at(i)->update(m_x, m_y, m_z);
        }
    }
    void setData(string x, string y, string z){
        bool check = false;
        if(m_x !=x){
            m_x = x;
            check = true;
        }
        if(m_y !=y){
            m_y = y;
            check = true;
        }
        if(m_z !=z){
            m_z = z;
            check = true;
        }
        if(check)   notifyObserver();
    }
};
class DisplayOne: public baseIObserver, public IDisplay{
public:
    DisplayOne(){
    }
    void update(int x, int y, int z){
        cout << x << " " << y << " " << z << endl;
        cout << x+y+z << endl;
        display();
    }
    void update(string x, string y, string z){
        cout << x << " " << y << " " << z << endl;
        cout << x+y+z << endl;
        display();
    }
    void display(){
        cout << "updated display one" << endl;
    }
};
class DisplayTwo: public baseIObserver, public IDisplay{
public:
    DisplayTwo(){
    }
    void update(int x, int y, int z){
        cout << x << " " << y << " " << z << endl;
        cout << -x-y-z << endl;
        display();
    }
    void update(string x, string y, string z){
        cout << x << " " << y << " " << z << endl;
        cout << x+y+z << endl;
        display();
    }
    void display(){
        cout << "updated display two" << endl;
    }
};
int main(int argc, char *argv[])
{
    WeatherData* sub = new WeatherData;
    WeatherDataAgain* subAgain = new WeatherDataAgain;

    baseIObserver* allOb[2];
    allOb[0] = new DisplayOne;
    allOb[1] = new DisplayTwo;

    allOb[0]->addSubject(sub);
    allOb[0]->addSubject(subAgain);
    allOb[1]->addSubject(subAgain);
//    sub->setData(1,2,3);
    subAgain->setData("1","2","3");
    return 0;
}
