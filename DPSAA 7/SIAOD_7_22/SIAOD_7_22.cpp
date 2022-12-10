#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <map>

using namespace std;

typedef std::pair<unsigned char, double> pair_for_Shennon_Fano;

///////////////////////////////////////////// RLE //////////////////////////////////////////////////////////////

void addRepeatSequenceToRLE(vector<unsigned char>& rle, char el, int& start, int end)
{
    unsigned char serviceByte = 128;
    serviceByte += end - start;
    rle.push_back(serviceByte);
    rle.push_back(el);
    start = end; //Обновляем начальные границы
}

void addDifferenceSequenceToRLE(vector<unsigned char>& rle, string source, int& start, int end)
{
    char serviceByte = 0;
    serviceByte += end - start;
    rle.push_back(serviceByte);
    for (int i = start; i < end; i++)
    {
        rle.push_back(source[i]);
    }
    start = end; //Обновляем начальные границы
}

unsigned char* RLE(string str, int& size)
{
    vector<unsigned char> result;
    int startRepeatSequence = 0;
    int startDifferenceSequence = 0;

    char serviceByte;
    for (int i = 1; i < str.length(); i++)
    {
        if (str[i] == str[startRepeatSequence] && str[i-1] == str[i] && (i + 1 == str.length() || str[i + 1] != str[startRepeatSequence])) //Запись повторяющихся элементов в массив
        {
            addRepeatSequenceToRLE(result, str[i], startRepeatSequence, i + 1);
            startDifferenceSequence = startRepeatSequence;
        }
        else if (str[i] != str[startRepeatSequence] && (i + 1 == str.length() || str[i + 1] == str[i]))
        {
            if (i + 1 == str.length()) addDifferenceSequenceToRLE(result, str, startDifferenceSequence, str.length());
            else addDifferenceSequenceToRLE(result, str, startDifferenceSequence, i);

            startRepeatSequence = i;
        }
    }

    unsigned char* res = new unsigned char[result.size()];
    size = result.size();
    for (int i = 0; i < result.size(); i++)
    {
        res[i] = result[i];
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// LZ77 ////////////////////////////////////////////////////////

struct LZ77Node
{
    int offset = 0;
    int length = 0;
    char next = 0;
};

bool isSubstrInBuffer(int& offset, int& length, string buffer, string substr)
{
    length = substr.length();
    if (substr.length() < buffer.length())
    {
        int finalOffset = -1;
        int substrSize = 0;
        int startIndexSubstr = 0;
        for (int strIndex = 0; strIndex < buffer.length(); strIndex++)
        {
            if (buffer[strIndex] == substr[substrSize])
            {
                if (substrSize == 0) startIndexSubstr = strIndex;
                substrSize++;
            }
            else
            {
                substrSize = 0;
                startIndexSubstr = -1;
            }

            if (substrSize == substr.length())
            {
                finalOffset = startIndexSubstr;
                startIndexSubstr = 0;
                substrSize = 0;
            }
        }
        if (finalOffset != -1)
        {
            offset = buffer.length() - finalOffset;
            return true;
        }
        return false;
    }
    else
    {
        int substrIndex = 0;
        bool getOut = false;
        for (int bufferIndex = 0; bufferIndex < buffer.length(); )
        {
            if (buffer[bufferIndex] == substr[substrIndex])
            {
                if (getOut == false) offset = buffer.length() - bufferIndex;
                
                getOut = true;
                if (substrIndex == substr.length() - 1) return true;
                bufferIndex++;
                substrIndex++;
                if (bufferIndex == buffer.length()) bufferIndex = 0; //Для циклического обхода в буффере
                
                continue;
            }
            if (buffer[bufferIndex] != substr[substrIndex] && getOut) return false;
            bufferIndex++;
        }
        return false;
    }
}

vector<LZ77Node> LZ77(string str)
{
    vector<LZ77Node> result;
    int indexStartBuffer = 0;
    int indexEndBuffer = 0;

    int indexWindow = 0;
    for (int offsetWindow = 0; offsetWindow < str.length(); offsetWindow++)
    {
        LZ77Node node;
        if (isSubstrInBuffer(node.offset, node.length, str.substr(indexStartBuffer, indexEndBuffer - indexStartBuffer), str.substr(indexWindow, offsetWindow - indexWindow + 1)))
        {
            if (offsetWindow == str.length() - 1) //Если элемент один
            {
                node.next = '\0';
                result.push_back(node);
            }
        }
        else
        {
            int additionalOffset = 0; //Для одного элемента
            if (offsetWindow - indexWindow == 0) additionalOffset++;

            isSubstrInBuffer(node.offset, node.length, str.substr(indexStartBuffer, indexEndBuffer - indexStartBuffer), str.substr(indexWindow, offsetWindow - indexWindow + additionalOffset));

            if (offsetWindow - indexWindow == 0) node.length = 0; //Для одного элемента
            node.next = str[offsetWindow];
            result.push_back(node);
            
            indexEndBuffer = offsetWindow + 1; //Смешение буффера и окна
            indexWindow = offsetWindow + 1;
            while (indexEndBuffer - indexStartBuffer > 4) indexStartBuffer++;
        }
    }
    return result;
}

string encodeLZ77(vector<LZ77Node> code)
{
    string result = "";
    for (int i = 0; i < code.size(); i++)
    {
        int startBuffer = result.length() - 1 - 4;
        int endBuffer = result.length() - 1;
        while (startBuffer < 0) startBuffer++;

        int position = result.length() - code[i].offset;
        for (int j = 0; j < code[i].length; j++)
        {
            result += result[position] ;
            position++;
            if (position > endBuffer) position = startBuffer;
        }
        result += code[i].next;
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// LZ78 ////////////////////////////////////////////////////////

struct LZ78Node
{
    int pref = 0;
    char symb = 0;  
};

bool checkPrefix(vector<string> source, string pref, int& index)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i]== pref)
        {
            index = i;
            return true;
        }
    }
    index = -1;
    return false;
}

vector<LZ78Node> LZ78(string str, vector<string>& dictionary)
{
    vector<LZ78Node> result;
    vector<string> pref;

    int startIndex = 0;
    int endIndex = 0;
    int pair_index = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (checkPrefix(pref, str.substr(startIndex, endIndex - startIndex + 1),pair_index) == false || i == str.length() - 1)
        {
            if (endIndex - startIndex == 0)
            {
                pref.push_back(str.substr(startIndex, endIndex - startIndex + 1));
                LZ78Node node;
                node.pref = 0;
                node.symb = str[i];
                result.push_back(node);
            }
            else
            {
                for (int j = 0; j < pref.size(); j++)
                {
                    if (pref[j] == str.substr(startIndex, endIndex - startIndex))
                    {
                        pref.push_back(str.substr(startIndex, endIndex - startIndex + 1));
                        LZ78Node node;
                        node.pref = j + 1;
                        node.symb = str[i];
                        result.push_back(node);
                        break;
                    }
                }
            }
            startIndex = endIndex = i + 1;
        }
        else
        {
            endIndex++;
        }
    }
    dictionary = pref;
    return result;
}

string encodeLZ78(vector<LZ78Node> code, vector<string> dictionary)
{
    string result = "";
    for (int i = 0; i < code.size(); i++)
    {
        if (code[i].pref == 0) result += code[i].symb;
        else
        {
            result += dictionary[code[i].pref - 1] + code[i].symb;
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// Шеннон-Фано //////////////////////////////////////////////////////////

struct nodeShennon_Fano
{
    unsigned char value = 0;
    string code = "";

    nodeShennon_Fano* zero = nullptr;
    nodeShennon_Fano* one = nullptr;
};

vector<pair_for_Shennon_Fano> makeProbabilitiesTable(string str)
{
    //Создание таблицы вероятнестей элементов
    map<unsigned char, double> dictTable;
    for (int i = 0; i < str.length(); i++)
    {
        dictTable[str[i]] += 1;
    }
    for (auto it = dictTable.begin(); it != dictTable.end(); it++)
    {
        it->second = round(it->second / str.length() * 10000) / 10000;
    }

    vector<pair_for_Shennon_Fano> table;
    copy(dictTable.begin(), dictTable.end(), back_inserter<vector<pair_for_Shennon_Fano>>(table));
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = i + 1; j < table.size(); j++)
        {
            if (table[i].second > table[j].second) swap(table[i], table[j]);
        }
    }
    return table;
}

void createFanotree(nodeShennon_Fano* parent, const vector<pair_for_Shennon_Fano> setOfSymbols, int start, int end, double balance = 1, bool isZero = false)
{
    if (end - start == 0) parent->value = setOfSymbols[start].first;
    else
    {
        parent->zero = new nodeShennon_Fano;
        parent->zero->code = parent->code + "0";

        parent->one = new nodeShennon_Fano;
        parent->one->code = parent->code + "1";
        double currentWeightLeft = 0;
        for (int i = start; i <= end; i++)
        {
            if ((balance - currentWeightLeft <= 0.5 * balance + 0.015 || balance - currentWeightLeft <= 0.5 * balance - 0.015) && currentWeightLeft != 0)
            {

                createFanotree(parent->zero, setOfSymbols, start, i - 1, currentWeightLeft, true);
                createFanotree(parent->one, setOfSymbols, i, end, balance - currentWeightLeft, false);
                return;
            }
            else if (end - start == 1)
            {

                createFanotree(parent->zero, setOfSymbols, start, start, currentWeightLeft, true);
                createFanotree(parent->one, setOfSymbols, end, end, balance - currentWeightLeft, false);
                return;
            }
            else currentWeightLeft += setOfSymbols[i].second;
        }
    }
}

void searchElement(nodeShennon_Fano* parent, const unsigned char el, string& res)
{
    if (parent->value == el) res = parent->code;
    if (parent->zero != nullptr) searchElement(parent->zero, el, res);
    if (parent->one != nullptr) searchElement(parent->one, el, res);
}

unsigned char* Shennon_Fano(string str, int& size)
{
    auto table = makeProbabilitiesTable(str);

    nodeShennon_Fano* head = new nodeShennon_Fano;
    createFanotree(head, table, 0, table.size() - 1);

    //Составление битовой длины для последующего перевода в массив char
    string allBits = "";
    string sizeInBits;
    for (int i = 0; i < str.length(); i++)
    {
        searchElement(head, str[i], sizeInBits);
        allBits += sizeInBits;
    }

    //Округление до целого количества байт
    if ((double)allBits.length() / 8 != allBits.length() / 8)
    {
        int lastbits = (allBits.length() / 8 + 1) * 8 - allBits.length();
        for (int i = 0; i < lastbits; i++)
        {
            allBits = "0" + allBits;
        }
    }

    size = allBits.length() / 8;
    unsigned char* result = new unsigned char[size] {0};

    for (int byte = size - 1, bit = allBits.length() - 1; byte >= 0; byte--)
    {
        for (int j = 0; j < 8; j++, bit--)
        {
            result[byte] += (int)(allBits[bit] - '0') * pow(2, j);
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////// Хаффман //////////////////////////////////////////////////////

struct nodeHaffman
{
    unsigned char value = 0;
    int frequency = 0;
    string code = "";
    nodeHaffman* parent = nullptr;
    nodeHaffman* left = nullptr;
    nodeHaffman* right = nullptr;
};

vector<nodeHaffman*> makeFrequencyTable(string str)
{
    //Создание таблицы вероятнестей элементов
    map<unsigned char, double> table;
    for (int i = 0; i < str.length(); i++)
    {
        table[str[i]] += 1;
    }

    vector<nodeHaffman*> vec;
    for (auto iter = table.begin(); iter != table.end(); iter++)
    {
        nodeHaffman* node = new nodeHaffman;
        node->value = iter->first;
        node->frequency = iter->second;
        vec.push_back(node);
    }
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = i + 1; j < vec.size(); j++)
        {
            if (vec[i]->frequency > vec[j]->frequency) swap(vec[i], vec[j]);
        }
    }
    return vec;
}

void setCode(nodeHaffman* node, string code)
{
    node->code = node->parent->code + code;
    if (node->left != nullptr) setCode(node->left, "0");
    if (node->right != nullptr) setCode(node->right, "1");
}

void findInTree(nodeHaffman* node, const unsigned char symb, string& res)
{
    
    if (node->value == symb) res += node->code;
    if (node->left != nullptr) findInTree(node->left, symb, res);
    if (node->right != nullptr) findInTree(node->right, symb, res);
}

unsigned char* Haffman(string str, int& size)
{
    auto table = makeFrequencyTable(str);

    nodeHaffman* minNode;
    nodeHaffman* nextMinNode;

    nodeHaffman* trash1 = new nodeHaffman;
    trash1->frequency = INT32_MAX;
    nodeHaffman* trash2 = new nodeHaffman;
    trash2->frequency = INT32_MAX;
    nodeHaffman* head;
    //Формирование дерева
    while (true)
    {
        minNode = trash1;
        nextMinNode = trash2;
        nextMinNode->frequency = INT32_MAX;
        for (int i = 0; i < table.size(); i++)
        {
            nodeHaffman* temp = table[i];
            while (temp->parent != nullptr)
            {
                temp = temp->parent;
            }
            if (temp->frequency < minNode->frequency)
            {
                nextMinNode = minNode;
                minNode = temp;
            }
            else if (temp->frequency < nextMinNode->frequency && temp != minNode)
            {
                nextMinNode = temp;
            }
        }

        if (minNode == nextMinNode || nextMinNode->frequency == INT32_MAX)
        {
            head = minNode;
            break;
        }


        minNode->parent = new nodeHaffman;
        nextMinNode->parent = minNode->parent;
        minNode->parent->left = minNode;
        minNode->parent->right = nextMinNode;
        minNode->parent->frequency = minNode->frequency + nextMinNode->frequency;
    }
    
    if (head->left != nullptr) setCode(head->left, "0");
    if (head->right != nullptr) setCode(head->right, "1");

    string allBits = "";
    for (int i = 0; i < str.length(); i++)
    {
        findInTree(head, str[i], allBits);
    }

    //Округление до целого количества байт
    if ((double)allBits.length() / 8 != allBits.length() / 8)
    {
        int lastbits = (allBits.length() / 8 + 1) * 8 - allBits.length();
        for (int i = 0; i < lastbits; i++)
        {
            allBits = "0" + allBits;
        }
    }

    size = allBits.length() / 8;
    unsigned char* result = new unsigned char[size] {0};

    for (int byte = size - 1, bit = allBits.length() - 1; byte >= 0; byte--)
    {
        for (int j = 0; j < 8; j++, bit--)
        {
            result[byte] += (int)(allBits[bit] - '0') * pow(2, j);
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    system("chcp 1251 > null");
    int choice;
    string str;
    vector<LZ77Node> arrayLZ77;
    vector<LZ78Node> arrayLZ78;
    vector<string> tableLZ78;
    while (true)
    {
        cout << "1. Кодирование и вывод методом RLE\n2. Кодирование методом LZ77\n3. Декодирование LZ77\n4. Кодирование методом LZ78\n5. Декодирование LZ78\n6. Кодирование методом Шеннона-Фано\n7. Кодирвоание методом Хаффмана\n>> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Введите строку >> ";
            cin >> str;
            int size = 0;
            auto array = RLE(str, size);
            cout << "Размер: " << size << " байт" << endl;
            for (int i = 0; i < size; i++)
            {
                cout << hex << array[i] << " ";
            }
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Введите строку >> ";
            cin >> str;
            arrayLZ77 = LZ77(str);
            cout << "Размер: " << arrayLZ77.size() << " байт" << endl;
            for (int i = 0; i < arrayLZ77.size(); i++)
            {
                cout << "<" << arrayLZ77[i].offset << ", " << arrayLZ77[i].length << ", " << arrayLZ77[i].next << "> ";
            }
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Декодированная строка: " << encodeLZ77(arrayLZ77) << endl;
        }
        case 4:
        {
            cout << "Введите строку >> ";
            cin >> str;
            arrayLZ78 = LZ78(str,tableLZ78);
            cout << "Размер: " << arrayLZ78.size() << " байт" << endl;
            for (int i = 0; i < arrayLZ78.size(); i++)
            {
                cout << "<" << arrayLZ78[i].pref << ", " << arrayLZ78[i].symb << "> ";
            }
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "Декодированная строка: " << encodeLZ78(arrayLZ78, tableLZ78) << endl;
        }
        case 6:
        {
            cout << "Введите строку >> ";
            cin >> str;
            int size = 0;
            auto array = Shennon_Fano(str, size);
            cout << "Размер: " << size << " байт" << endl;
            for (int i = 0; i < size; i++)
            {
                cout << hex << array[i] << " ";
            }
            cout << endl;
            break;
        }
        case 7:
        {
            cout << "Введите строку >> ";
            cin >> str;
            int size = 0;
            auto array = Haffman(str, size);
            cout << "Размер: " << size << " байт" << endl;
            for (int i = 0; i < size; i++)
            {
                cout << hex << array[i] << " ";
            }
            cout << endl;
            break;
        }
        default:
            cout << "Завершение программы..." << endl;
            break;
        }
    }
}
