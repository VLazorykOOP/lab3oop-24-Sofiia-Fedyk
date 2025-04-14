#include <iostream>
#include <stdexcept>

class Vector {
private:
    int* data;
    int size;
    static int count;

public:
    // Конструктори
    Vector() : size(1) { data = new int[1](); count++; }
    
    Vector(int vectorSize) : size(vectorSize > 0 ? vectorSize : 1) {
        data = new int[size]();
        count++;
    }
    
    Vector(int vectorSize, int initValue) : size(vectorSize > 0 ? vectorSize : 1) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = initValue;
        count++;
    }
    
    // Конструктор копій і оператор присвоєння
    Vector(const Vector& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        count++;
    }
    
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }
    
    // Деструктор
    ~Vector() { delete[] data; count--; }
    
    // Методи доступу
    void setValue(int index, int value = 0) {
        if (index < 0 || index >= size) throw std::out_of_range("Індекс за межами");
        data[index] = value;
    }
    
    int getValue(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Індекс за межами");
        return data[index];
    }
    
    // Арифметичні операції
    Vector add(const Vector& other) const {
        if (size != other.size) throw std::invalid_argument("Різні розміри");
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }
    
    Vector subtract(const Vector& other) const {
        if (size != other.size) throw std::invalid_argument("Різні розміри");
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }
    
    Vector multiply(short scalar) const {
        Vector result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * scalar;
        return result;
    }
    
    // Порівняння
    bool isGreater(const Vector& other) const {
        if (size != other.size) throw std::invalid_argument("Різні розміри");
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < size; i++) { sum1 += data[i]; sum2 += other.data[i]; }
        return sum1 > sum2;
    }
    
    bool isLess(const Vector& other) const {
        if (size != other.size) throw std::invalid_argument("Різні розміри");
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < size; i++) { sum1 += data[i]; sum2 += other.data[i]; }
        return sum1 < sum2;
    }
    
    bool isEqual(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) 
            if (data[i] != other.data[i]) return false;
        return true;
    }
    
    // Додаткові методи
    void print() const {
        std::cout << "[ ";
        for (int i = 0; i < size; i++) 
            std::cout << data[i] << (i < size - 1 ? ", " : "");
        std::cout << " ]" << std::endl;
    }
    
    int getSize() const { return size; }
    static int getCount() { return count; }
};

int Vector::count = 0;

// Скорочена тестова програма
int main() {
    try {
        // Тестування конструкторів
        Vector v1;
        Vector v2(5);
        Vector v3(3, 7);
        
        std::cout << "v1: "; v1.print();
        std::cout << "v2: "; v2.print();
        std::cout << "v3: "; v3.print();
        
        // Копіювання і присвоєння
        Vector v4(v3);
        std::cout << "v4 (копія v3): "; v4.print();
        
        Vector v5;
        v5 = v2;
        std::cout << "v5 (= v2): "; v5.print();
        
        // Встановлення/отримання значень
        v5.setValue(1, 10);
        v5.setValue(3, 30);
        std::cout << "v5 після setValue: "; v5.print();
        
        // Арифметичні операції
        Vector a(3, 5), b(3, 2);
        std::cout << "a: "; a.print();
        std::cout << "b: "; b.print();
        
        Vector sum = a.add(b);
        std::cout << "a + b: "; sum.print();
        
        Vector diff = a.subtract(b);
        std::cout << "a - b: "; diff.print();
        
        Vector prod = a.multiply(3);
        std::cout << "a * 3: "; prod.print();
        
        // Порівняння
        Vector d(3, 5), e(3, 7), f(3, 3);
        std::cout << "a == d: " << (a.isEqual(d) ? "true" : "false") << std::endl;
        std::cout << "a > f: " << (a.isGreater(f) ? "true" : "false") << std::endl;
        std::cout << "a < e: " << (a.isLess(e) ? "true" : "false") << std::endl;
        
        // Обробка винятків
        try {
            v5.setValue(10, 100);
        } catch (const std::out_of_range& e) {
            std::cout << "Помилка: " << e.what() << std::endl;
        }
        
        std::cout << "Кількість об'єктів: " << Vector::getCount() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Загальна помилка: " << e.what() << std::endl;
    }
    
    return 0;
}