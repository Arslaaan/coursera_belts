#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human( const string& name, const string& type = "Human" )
            : Name( name ), Type( type ) {}

    // getting rid of duplicate code
    void PrintResponse( const string& response ) const
    {
        cout << Type << ": " << Name << " " << response << endl;
    }

    virtual void Walk( const string& destination ) const
    {
        PrintResponse( "walks to: " + destination );
    }

    void VisitPlaces( const vector<string>& places ) const
    {
        for ( const auto& p : places )
        {
            Walk( p );
        }
    }

    string getName() const
    {
        return Name;
    }

    string getType() const
    {
        return Type;
    }

private:
    const string Name;
    const string Type;
};

class Student : public Human
{
public:

    Student( const string& name, const string& favouriteSong )
            : Human( name, "Student" ), FavouriteSong( favouriteSong ) {}

    void Learn() const
    {
        PrintResponse( "learns" );
    }

    void Walk( const string& destination ) const override
    {
        Human::Walk( destination );
        SingSong();
    }

    void SingSong() const
    {
        PrintResponse( "sings a song: " + FavouriteSong );
    }

private:
    const string FavouriteSong;
};


class Teacher : public Human
{
public:

    Teacher( const string& name, const string& subject )
            : Human( name, "Teacher" ), Subject( subject ) {}

    void Teach() const
    {
        PrintResponse( "teaches: " + Subject );
    }

private:
    const string Subject;
};


class Policeman : public Human
{
public:
    Policeman( const string& name ) : Human( name, "Policeman" ) {}

    void Check( const Human& h ) const
    {
        PrintResponse( "checks " + h.getType() + ". " + h.getType() + "'s name is: " + h.getName() );
    }
};

int main()
{
    Teacher t( "Jim", "Math" );
    Student s( "Ann", "We will rock you" );
    Policeman p( "Bob" );

    t.VisitPlaces({ "Moscow", "London" } );
    p.Check( s );
    s.VisitPlaces( { "Moscow", "London" } );
    return 0;
}