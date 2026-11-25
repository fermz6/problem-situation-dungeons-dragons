/*
Description: Monster header, establishes the attributes and function declarations
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#pragma once
#include <string>

class Monster {
    private:
        std::string name;
        double cr;
        std::string type;
        std::string size;
        int ac;
        int hp;
        std::string align;

    public:
        Monster();
        Monster(std::string name, double cr, std::string type, std::string size, int ac, int hp, std::string align);
        ~Monster();

        std::string getName() const; // Const so that we can print the room using monster functions and not modify them
        void setName(std::string name);

        double getCr();
        void setCr(double cr);

        std::string getType();
        void setType(std::string type);

        std::string getSize();
        void setSize(std::string size);

        int getAc() const;
        void setAc(int ac);

        int getHp() const;
        void setHp(int hp);

        std::string getAlign();
        void setAlign(std::string align);

        bool operator<(const Monster& other) const;
        bool operator>(const Monster& other) const;
        bool operator==(const Monster& other) const;
        bool operator!=(const Monster& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Monster& monster);
};