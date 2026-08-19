#include "inv.h"
#include <iostream>

char inv::invinside[17][35] = {
        "_================================_",
        "||      ||      ||      ||      ||",
        "||  1   ||  ?   ||  ?   ||  ?   ||",
        "||      ||      ||      ||      ||",
        "||==============================||",
        "||      ||      ||      ||      ||",
        "||  2   ||  ?   ||  ?   ||  ?   ||",
        "||      ||      ||      ||      ||",
        "||==============================||",
        "||      ||      ||      ||      ||",
        "||  3   ||  ?   ||  ?   ||  ?   ||",
        "||      ||      ||      ||      ||",
        "||==============================||",
        "||      ||      ||      ||      ||",
        "||  4   ||  ?   ||  ?   ||  ?   ||",
        "||      ||      ||      ||      ||",
        "-================================-"
};

void inv::OpenInv() const
{
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 34; j++) {
            std::cout << invinside[i][j];
        }
        std::cout << std::endl;
    }
}

void inv::RecivedInv(char thing) const
{
    char changed = 'N';
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 35; j++) {
            if (invinside[i][j] == '?') {
                invinside[i][j] = thing;
                changed = 'Y';
                return;
            }
        }
    }
    if (changed != 'Y') {
        std::cout << "Invantory full, cant store" << std::endl;
    }
}