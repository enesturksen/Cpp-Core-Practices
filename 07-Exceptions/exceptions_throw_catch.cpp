#include <iostream>

// 1. GELENEKSEL YÖNTEM: Hata durumunu referansla (bool&) bildirme
// Fonksiyon sadece tek bir değer dönebildiği için hata kontrolü dışarıdan taşınır.
double bolmeGeleneksel(int a, int b, bool& basarili) {
    if (b == 0) {
        basarili = false; // main fonksiyonundaki değişkeni doğrudan etkiler
        return 0;         // Geçersiz sonuç
    }
    basarili = true;
    return (double)a / b;
}

// 2. MODERN C++ YÖNTEMİ: İstisna Fırlatma (throw)
// Hata oluştuğu an kırmızı bayrak kalkar, fonksiyonun çalışması anında durur.
double bolmeModern(int a, int b) {
    if (b == 0) {
        // Çift tırnaklı metin fırlatıldığı için veri tipi "const char*" olur
        throw "Hata: Payda sifir olamaz!";
    }
    return (double)a / b;
}

int main() {
    // --- 1. TEST: Geleneksel Yöntemin Kusuru ---
    bool islemDurumu = true;
    double sonucEski = bolmeGeleneksel(10, 0, islemDurumu);

    // Her işlemden sonra elle "if" yazıp kontrol etme zorunluluğu kodu uzatır:
    if (!islemDurumu) {
        std::cout << "[Geleneksel Yontem] Islem basarisiz. Gecersiz sonuc: " << sonucEski << "\n\n";
    }

    // --- 2. TEST: Modern İstisna Mekanizması (try - catch) ---
    try {
        // Korumalı bölge: Hata fırlatma riski taşıyan işlemler buraya yazılır
        std::cout << "[Modern Yontem] 10 / 2 = " << bolmeModern(10, 2) << "\n";

        // Bu fonksiyon çağrısında bölen 0 olduğu için 'throw' çalışır:
        std::cout << "[Modern Yontem] 10 / 0 = " << bolmeModern(10, 0) << "\n";

        // 'throw' akışı kestiği için bu satır ve altındakiler ASLA çalıştırılmaz:
        std::cout << "Bu satir ekrana basilmayacak.\n";
    }
    // Tip Eşleşmesi: Fırlatılan değer metin olduğundan 'const char*' tipiyle karşılanır:
    catch (const char* hataMesaji) {
        // Program çökmedi; hata güvenli bir şekilde yakalandı ve yönetildi:
        std::cout << "[Catch Blogu] Istisna yakalandi -> " << hataMesaji << "\n";
    }

    // İstisna yakalandığı için program hayatına kaldığı yerden devam eder:
    std::cout << "\nProgram cokmeden basariyla sonlandi.\n";

    return 0;
}