// WAR: THE CARD GAME
#include <bits/stdc++.h>
using namespace std;

#define max_deck_size 52;
#define num_rank 13;
#define num_suit 4;

enum Rank
{
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};
enum Suit
{
    SPADES,
    HEART,
    DIAMOND,
    CLUBS
};

class Card
{
public:
    Rank rank;
    Suit suit;
};

// deck is a class which creates a linked list of cards
class Deck
{
public:
    Card card;
    Deck *next;
    Deck(int s, int r)
    {
        card.rank = Rank(r);
        card.suit = Suit(s);
        next = NULL;
    }
} *atop, *btop, *bbot, *abot;

void war(vector<Deck>);
void compare(vector<Deck>);
// DECK OF CARDS SHOULD PERFORM THE FOLLOWING FUNCTION
// 1.CREATE AN EMPTY DECK
// ADD OBJECT TO BOTTOM OF DECK
// REMOVE THE OBJECT AT TOP OF THE DECK IF IT'S EMPTY THEN RETURN NULL
// TESTS WHETHER DECK IS EMPTY
// RANDOMIZE THE ORDER OF CARDS IN A DECK
// RETURNS THE NO OF CARDS IN A DECK
// FUNCTION TO CREATE A DECK OF 52 CARDS
void initialize_deck(Deck *&head)
{
    Deck *temp = head;

    for (int s = 0; s < 4; s++)
    {
        for (int r = 0; r < 13; r++)
        {

            Deck *d = new Deck(s, r);
            if (r == 0 && s == 0)
            {
                continue;
            }
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = d;
        }
    }
}

string card_name(int suit, int rank)
{
    string s1 = " ";
    if (rank == 0)
        s1 += "Ace";
    else if (rank == 1)
        s1 += "two";
    else if (rank == 2)
        s1 += "three";
    else if (rank == 3)
        s1 += "four";
    else if (rank == 4)
        s1 += "five";
    else if (rank == 5)
        s1 += "six";
    else if (rank == 6)
        s1 += "seven";
    else if (rank == 7)
        s1 += "eight";
    else if (rank == 8)
        s1 += "nine";
    else if (rank == 9)
        s1 += "ten";
    else if (rank == 10)
        s1 += "Jack";
    else if (rank == 11)
        s1 += "Queen";
    else if (rank == 12)
        s1 += "King";
    s1 += " of ";
    if (suit == 0)
        s1 += "diamond";
    else if (suit == 1)
        s1 += "spade";
    else if (suit == 2)
        s1 += "club";
    else if (suit == 3)
        s1 += "heart";

    return s1;
}

void display_deck(Deck *head)
{
    Deck *temp = head;
    while (temp != NULL)
    {
        cout << "RANK=" << temp->card.rank << " ";
        cout << "SUIT=" << temp->card.suit << " " << card_name(temp->card.suit, temp->card.rank) << endl;
        temp = temp->next;
    }
}

// FUNCTION TO DIVIDE THE LINKED LIST INTO TWO PARTS
void deal(Deck *head, Deck *&atop, Deck *&btop, Deck *&abot, Deck *&bbot)
{
    Deck *temp = head;
    atop = temp;
    abot = temp;
    temp = temp->next;
    btop = temp;
    bbot = temp;
    temp = temp->next;
    while (temp != NULL)
    {
        abot->next = temp;
        abot = temp;
        temp = temp->next;
        bbot->next = temp;
        bbot = temp;
        temp = temp->next;
    }
    abot->next = NULL;
    bbot->next = NULL;
}

// FUNCTION TO SHUFFLE CARDS OF DECK
void shuffle_deck(Deck *head)
{
    // insert element of deck to a vector
    Deck *temp = head;
    int r, s;
    vector<pair<int, int>> vect;
    while (temp != NULL)
    {
        r = (int)temp->card.rank;
        s = (int)temp->card.suit;
        vect.push_back(make_pair(r, s));
        temp = temp->next;
    }
    unsigned seed = 0;
    shuffle(vect.begin(), vect.end(), default_random_engine(seed));
    cout << endl
         << "The cards are shuffled" << endl;
    Deck *insert = head;

    for (int i = 0; i < vect.size(); i++)
    {
        insert->card.rank = (Rank)(vect[i].first);
        insert->card.suit = (Suit)(vect[i].second);
        insert = insert->next;
    }
}

// FUNCTION TO POP CARD FROM DECK
Deck pop(Deck **atop)
{
    Deck temp = *(*atop);
    (*atop) = (*atop)->next;
    temp.next = NULL;
    return temp;
}

// FUNCTION TO RETURN COUNT OF CARDS IN A DECK
int countDeck(Deck **h)
{
    int count = 0;
    Deck *temp = *h;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// FUNCTION TO DISPLAY END GAME MESSAGE
void endGame()
{
    int count1 = countDeck(&atop);
    int count2 = countDeck(&btop);
    char c = (count1 > count2) ? 'A' : 'B';
    cout << "\nTHE GAME HAS ENDED\n";
    cout << "\nDeck size of PLAYER A: " << countDeck(&atop) << "\n";
    cout << "Deck size of PLAYER B: " << countDeck(&btop) << "\n";
    if (count1 == count2)
    {
        cout << "\nGAME DRAWN\n";
    }
    else
        cout << "\nPLAYER " << c << " HAS WON\n";
}

// FUNCTION TO COMPARE CARDS FROM TOP
void compare(vector<Deck> c)
{
    int count1 = countDeck(&atop);
    int count2 = countDeck(&btop);
    if (count1 == 0 || count2 == 0)
        endGame();
    cout << endl
         << "Deck size of PLAYER A is:" << count1 << endl
         << "Deck size of PLAYER B is:" << count2 << endl;
    cout << endl
         << "PLAYER A DREW:" << card_name(atop->card.suit, atop->card.rank);
    cout << endl
         << "PLAYER B DREW:" << card_name(btop->card.suit, btop->card.rank);
    if (atop->card.rank > btop->card.rank)
    {
        cout << endl
             << "PLAYER A HAS WON";

        {
            abot->next = btop;
            btop = btop->next;
            abot = abot->next;
            abot->next = atop;
            abot = abot->next;
            atop = atop->next;
        }
        bbot->next = NULL;
        abot->next = NULL;

        cout << endl
             << "2 CARDS HAVE BEEN SUCCEESSFULLY ADDED TO BOTTOM OF LIST" << endl;
        count1++;
        count2--;
        for (int i = 0; i < c.size(); i++)
        {
            abot->next = &c[i];
            abot = abot->next;
        }
        c.clear();
        cout << "PLAYER A now has " << count1 << " cards and player B has " << count2 << " cards" << endl;
        if (count2 == 0)
        {
            cout << "PLAYER B IS OUT OF CARDS! WINNER OF THE GAME IS PLAYER A" << endl;
            return;
        }
    }

    else if (btop->card.rank > atop->card.rank)
    {
        cout << endl
             << "PLAYER B HAS WON" << endl;
        {
            bbot->next = atop;
            atop = atop->next;
            bbot = bbot->next;
            bbot->next = btop;
            bbot = bbot->next;
            btop = btop->next;
        }
        abot->next = NULL;
        bbot->next = NULL;
        cout << "2 CARDS HAVE BEEN ADDED SUCCESSFULLY TO THE DECK" << endl;
        count2++;
        count1--;
        for (int i = 0; i < c.size(); i++)
        {
            bbot->next = &c[i];
            bbot = bbot->next;
        }
        c.clear();
        cout << "PLAYER 1 now has " << count1 << " cards and player 2 has " << count2 << " cards" << endl;
        if (count1 == 0)
        {
            cout << "PLAYER A IS OUT OF CARDS! PLAYER B HAS WON THE GAME";
            return;
        }
    }
    else if (btop->card.rank == atop->card.rank)
    {
        cout << endl
             << "YOU BOTH HAVE THE SAME RANKS" << endl;
        cout << endl
             << "IT'S TIME FOR WAR!" << endl;

        c.push_back(pop(&atop));

        c.push_back(pop(&btop));
        war(c);
    }
}

void war(vector<Deck> c)
{
    c.push_back(pop(&atop));
    Deck temp1 = pop(&atop);
    temp1.next = atop;
    atop = &temp1;
    c.push_back(temp1);

    c.push_back(pop(&btop));

    Deck temp2 = pop(&btop);
    temp2.next = btop;
    btop = &temp2;
    c.push_back(temp2);
    compare(c);
}

int main()
{
    Deck *head = new Deck(0, 0);
    int choice;
    initialize_deck(head);
    cout << endl
         << "Welcome to the WAR of cards" << endl;
    cout << endl
         << "preparing the deck of cards to be played" << endl;
    cout << endl
         << "do you want to see the standard deck of cards(y/n)?";
    char y;
    cin >> y;
    if (y == 'Y' || y == 'y')
    {
        cout << endl
             << "THE STANDARD DECK OF CARDS ARE:" << endl;
        display_deck(head);
    }
    cout << "Press y to start the game and n to exit" << endl;
    char ch;
    cin >> ch;
    if (ch == 'n')
        exit(0);
    cout << "it's you vs computer" << endl;
    deal(head, atop, btop, abot, bbot);
    cout << "deck size is:26" << endl;
    // cout<<endl<<"each deck contains:"<<endl;
    // display_deck(atop);
    cout << endl;
    vector<Deck> c;
    // display_deck(btop);
    do
    {
        cout << "\n1.shuffle the deck" << endl;
        cout << "2.draw the card" << endl;
        cout << "3.exit" << endl;
        cout << endl
             << "enter your choice of action: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            shuffle_deck(btop);
            // cout<<"your cards after shuffling are"<<endl;
            // display_deck(btop);
            break;
        case 2:
            compare(c);
            break;
        case 3:
            endGame();
            exit(0);
        }
    } while (choice != 3);
}