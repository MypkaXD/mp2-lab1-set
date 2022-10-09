// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) {
        (throw "ERROR: negative lenght");
    }
    BitLen = len;
    MemLen = BitLen / (sizeof(TELEM) * 8) + 1; //кол-во элеметов TELEM для хранения всего множества
    pMem = new TELEM[MemLen];

    if (pMem != NULL) {
        for (int count = 0; count < MemLen; count++) {
            pMem[count] = 0;
        }
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{

}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    /*
         Нужно ли обрабатывать эту ошибку ? ведь по факту мы получаем index какого - то бита n(допустим 156).
         Само битовое поле состоит из 172 (но в массиве 171 индекс, так как начало с 0). Всего получается MemLen = 6, кол-во бит,
         которое она сможет хранить = 6 * sizeoff(TELEM) * 8 - 1 (так как массив). То есть всего 191 индекс в массиве для хранения битов, 191-171=20, которые из них не заняты.
         По факту они нам не нужны, мы их не инициализировали (только в начале 0, когда создали массив pMem)
         Какой-то важной информации для пользователя там нет, поэтому надо использовать BitLen - 1, a не sizeof(TELEM) * 8 * MemLen - 1
         Деже если мы в будущем добавим какой-то элемент, то нам придется увеличить BitLen++, иначе будет не логично, ведь BitLen хранит в себе мощность |U|.
    */
    if (n > BitLen - 1) {
        throw ("ERROR: unknown index");
    }
    /*
        На всякий случай обработаю и такую ошибку, вдруг понадобится, но ведь если рассмотреть создание Битового поля, эта ошибка там рассматривается, то есть
        мы не сможем создать отрицательное битовое поле (|U| >= 0). Поэтому здесь нет смысла рассматривать её, ведь этот метод не статичный, то есть мы не можем
        вызвать его без создания Битового поля.
    */
    if (n < 0) {
        (throw "ERROR: negative lenght");
    }

    return n / (sizeof(TELEM) * 8);
    /*
        если мы ищем индекс Мем для 15 - ого бита, то нам понадобится 15 / кол - во бит в одном TELEM.Пример 15 / 64 = 0
        (деления нацело) 128 / 64 = 2. Не забываем, что отсчет в массиве идет с 0
    */
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    /*
        если я правильно понял, то маска, это такое число типа TELEM, которое в двоичном представлении имеет 1 еденичку и все оставшиеся элементы = 0
        Вопрос только стомт в том, надо ли писать n-1 или просто n.
    */
    return (1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    TELEM mask = GetMemMask(n);
    int index = GetMemIndex(n);
    pMem[index] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    TELEM mask = GetMemMask(n);
    int index = GetMemIndex(n);
    pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    TELEM mask = GetMemMask(n);
    int index = GetMemIndex(n);
    return bool(pMem[index] & mask);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) {
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
    }

    for (int count = 0; count < MemLen; count++)
        pMem[count] = bf.pMem[count];

    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return false; //посылаем 0, так как разные длины, следовательно !=
    else
        for (int count = 0; count < MemLen; count++)
            if (pMem[count] != bf.pMem[count]) {
                return false;//посылаем 0, так как разные значения битов[count], следовательно !=
            }
    return true; //посылаем 1, все норм
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(bf == *this);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int maxLenght = std::max(BitLen, bf.BitLen);

    TBitField tempBitField(maxLenght);

    for (int count = 0; count < MemLen; count++) {
        tempBitField.pMem[count] = pMem[count];
    }
    for (int count = 0; count < bf.MemLen; count++) {
        tempBitField.pMem[count] |= pMem[count];
    }

    return tempBitField;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int maxLenght = std::max(BitLen, bf.BitLen);

    TBitField tempBitField(maxLenght);

    for (int count = 0; count < MemLen; count++)
    {
        tempBitField.pMem[count] = pMem[count];
    }
    for (int count = 0; count < bf.MemLen; count++)
    {
        tempBitField.pMem[count] &= bf.pMem[count];
    }
    return tempBitField;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField other(BitLen);
    for (int count = 0; count < BitLen; count++) {
        if (GetBit(count))
            other.ClrBit(count);
        else
            other.SetBit(count);
    }
    return other;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char x;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> x;
        if (x == '0')
        {
            bf.ClrBit(i);
        }
        else if (x == '1')
        {
            bf.SetBit(i);
        }
        else
        {
            (throw "ERROR: Unknown type of bit");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
            ostr << '1';
        else
            ostr << '0';
    }
    return ostr;
}