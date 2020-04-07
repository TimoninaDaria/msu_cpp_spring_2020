#include "bigint.h"

BigInt::BigInt():
    len(1), sign(1) {
    number = new uint8_t[1];
    number[0] = 0;
}

BigInt::BigInt(const char* x):sign(1) {
    if (x[0] == '-'){
        sign = -1;
    }
    len = strlen(x);
    number = new uint8_t[len];
    for (int i = 0; i < len; ++i){
        number[i] = x[i] - '0';
    }
}

BigInt::BigInt(int64_t x):sign(1){
    int tmplen = 0;
    int64_t tmpx = x;

    if (x == 0) {
        len = 1;
        sign = 1;
        number = new uint8_t[1];
        number[0] = 0;
    }
    else{
        if (x < 0){
        x = (-1)*x;
        sign = -1;
        }

        while(tmpx){
            ++tmplen;
            tmpx = tmpx/10;
        }

        len = tmplen;
        number = new uint8_t[len];
        for (int i = len-1; i >= 0 ; --i){
            number[i] = x%10;
            x = x/10;
        }

    }
}

BigInt::~BigInt(){
    delete[] number;
}

BigInt::BigInt(const BigInt& copied): len(copied.len), sign(copied.sign){
    number = new uint8_t[len];
    for (int i=0; i < len; ++i) {
        number[i] = copied.number[i];
    }
}

BigInt& BigInt::operator=(const BigInt& copied){
    if (this == &copied)
        return *this;
    uint8_t* ptr = new uint8_t[copied.len];
    delete[] number;
    number = ptr;
    len = copied.len;
    sign = copied.sign;
    std::copy(copied.number, copied.number + len, number);
    return *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign + other.sign == 0) {
        if (sign == -1) {
            BigInt x(*this);
            x.sign = 1;
            BigInt y(other);
            BigInt tmp = y - x;
            return tmp;
        } else {
            BigInt x(*this);
            BigInt y(other);
            y.sign = 1;
            BigInt tmp = x - y;
            return tmp;
        }
    }
    int max_len, min_len, sum;
    uint8_t *max_num;
    BigInt tmp;
    if (len >= other.len) {
        max_len = len;
        min_len = other.len;
        max_num = number;
    } else {
        max_len = other.len;
        min_len = len;
        max_num = other.number;
      }
    tmp.len = max_len + 1;
    uint8_t* tmpptr = tmp.number;
    tmp.number = new uint8_t[max_len+1];
    delete[] tmpptr;
    tmp.sign = sign;
    for (int i=0; i < tmp.len; ++i) {
        tmp.number[i] = 0;
    }
    for (int i=0; i < min_len; ++i) {
        sum = number[len-1-i] + other.number[other.len-1-i]
                                + tmp.number[max_len-i];
        tmp.number[max_len-i] = sum % 10;
        tmp.number[max_len-1-i] += sum / 10;
    }
    for (int i=min_len; i < max_len; ++i) {
        sum = tmp.number[max_len-i] + max_num[max_len-1-i];
        tmp.number[max_len-i] = sum % 10;
        tmp.number[max_len-1-i] = sum / 10;
    }
    if (tmp.number[0] == 0) {
        uint8_t *res = new uint8_t[max_len];
        for (int i=max_len; i > 0; --i) {
            res[i-1] = tmp.number[i];
        }
        delete[] tmp.number;
        tmp.number = res;
        tmp.len = max_len;
    }
    return tmp;
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (sign + other.sign == 0) {
        if (sign == -1) {
            BigInt x(*this);
            BigInt y(other);
            y.sign = -1;
            BigInt tmp = x + y;
            return tmp;
        } else {
            BigInt x(*this);
            BigInt y(other);
            y.sign = 1;
            BigInt tmp = x + y;
            return tmp;
        }
    }
    int max_len, min_len, sum, equal = 1;
    uint8_t *max_num, *min_num;
    BigInt tmp;
    if (len > other.len) {
        max_len = len;
        min_len = other.len;
        max_num = number;
        min_num = other.number;
        tmp.sign = sign;
    } else if (len < other.len) {
        max_len = other.len;
        min_len = len;
        max_num = other.number;
        min_num = number;
        tmp.sign = -1 * other.sign;
    } else {
        max_len = min_len = len;
        for (int i=0; i < len; ++i) {
            if (number[i] > other.number[i]) {
                max_num = number;
                min_num = other.number;
                tmp.sign = sign;
                equal = 0;
                break;
            } else if (number[i] < other.number[i]) {
                max_num = other.number;
                min_num = number;
                tmp.sign = -1 * other.sign;
                equal = 0;
                break;
            }
        }
        if (equal == 1) {
            tmp.len = 1;
            tmp.sign = 1;
            uint8_t* tmpptr = tmp.number;
            tmp.number = new uint8_t[1];
            delete[] tmpptr;
            tmp.number[0] = 0;
            return tmp;
        }
    }
    tmp.len = max_len;
    uint8_t* tmpptr = tmp.number;
    tmp.number = new uint8_t[max_len];
    delete[] tmpptr;
    for (int i=0; i < tmp.len; ++i) {
        tmp.number[i] = 0;
    }
    for (int i=0; i < min_len; ++i) {
        sum = max_num[max_len-1-i] - min_num[min_len-1-i] + 10;
        tmp.number[max_len-1-i] += sum % 10;
        if (sum / 10 == 0) {
            tmp.number[max_len-2-i] = -1;
        }
        if (tmp.number[max_len-1-i] == -1) {
            tmp.number[max_len-1-i] = 9;
            tmp.number[max_len-2-i] = -1;
        }
    }
    for (int i=min_len; i < max_len; ++i) {
        tmp.number[max_len-1-i] += max_num[max_len-1-i];
        if (tmp.number[max_len-i-1] == -1) {
            tmp.number[max_len-i-1] = 9;
            tmp.number[max_len-i-2] = -1;
        }
    }
    int len_ = tmp.len;
    for (int i=0; i < tmp.len; ++i) {
        if (tmp.number[i] == 0) {
            len_--;
        } else {
            break;
        }
    }
    uint8_t *ptr = new uint8_t[len_];
    for (int i=0; i < len_; ++i) {
        ptr[len_-1-i] = tmp.number[tmp.len-1-i];
    }
    delete[] tmp.number;
    tmp.len = len_;
    tmp.number = ptr;
    return tmp;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.sign = -1;
    return tmp;
}

bool BigInt::operator==(const BigInt& other) const {
    if (this == &other) {
        return true;
    }
    if (len != other.len) {
        return false;
    }
    for (int i=0; i < len; ++i) {
        if (number[i] != other.number[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    if (this == &other) {
        return false;
    }
    if (sign * len > other.sign * other.len) {
        return true;
    } else if (sign * len < other.sign * other.len) {
        return false;
    }
    if (sign == 1 && other.sign == -1) {
        return true;
    } else if (sign == -1 && other.sign == 1) {
        return false;
    }
    for (int i=0; i < len; ++i) {
        if (number[i] > other.number[i]) {
            if (sign == 1)
                return true;
            else
                return false;
        } else if (number[i] < other.number[i]) {
            if (sign == 1)
                return false;
            else
                return true;
        }
    }
    return false;
}

bool BigInt::operator<(const BigInt& other) const {
    if (*this == other) {
        return false;
    }
    if (*this > other) {
        return false;
    }
    return true;
}

bool BigInt::operator>=(const BigInt& other) const {
    if (*this == other) {
          return true;
    }
    if (*this > other) {
        return true;
    }
    return false;
}

bool BigInt::operator<=(const BigInt& other) const {
    if (*this == other) {
        return true;
    }
    if (*this < other) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const BigInt& value) {
    if (value.sign == -1) {
        out << '-';
    }
    for (int i=0; i < value.len; ++i) {
        out << unsigned(value.number[i]);
    }
    return out;
}


