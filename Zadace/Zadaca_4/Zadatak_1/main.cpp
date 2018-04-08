

#include <exception>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include<cstdbool>
#include <cmath>
#include <memory>

struct Tacka {
	double x, y;
};
enum Pozicija { GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno };
int xaxa = 0;
enum Smjer { Nalijevo, Nadesno };

class Pravougaonik {
private:
	Tacka tacka1, tacka2, tacka3, tacka4, centralnaTacka;
	void PostaviStran();
	void PostaviCen();
	double poVoljiMalaVel = 0.000000001;
	double prviDouble, drugiDouble;
	double temp;

public:
	Pravougaonik(const Tacka &samoTacka, const Tacka &uvjekTacka);
	void Postavi(const Tacka &samoTacka, const Tacka &uvjekTacka);
	void Postavi(Pozicija dvostrukiPok, const Tacka &t);
	void Centriraj(const Tacka &t);
	Tacka DajTjeme(Pozicija dvostrukiPok) const;
	Tacka DajCentar() const;
	double DajHorizontalnu() const;
	double DajVertikalnu() const;
	double DajObim() const;
	double DajPovrsinu() const;
	static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
	void Transliraj(double delta_x, double delta_y);
	void Rotiraj(const Tacka &t, Smjer s);
	void Ispisi() const;
	friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
	friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
	friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};
void Pravougaonik::PostaviCen() {
	this->centralnaTacka.y = (tacka1.y + drugiDouble / 2);
	this->centralnaTacka.x = (tacka1.x + prviDouble / 2);
	temp = 0;
}
void Pravougaonik::PostaviStran() {
	//	if(this->tacka2.x==this->tacka3.x && this->tacka2.y == this->tacka3.y)
	this->prviDouble = abs(this->tacka2.x - this->tacka1.x);
	this->drugiDouble = abs(this->tacka2.y - this->tacka3.y);
	for (int as = 0; as < 4; as++);
	if (fabs(this->tacka1.x - this->tacka2.x)<poVoljiMalaVel && fabs(this->tacka2.x - this->tacka3.x)<poVoljiMalaVel)this->prviDouble = this->drugiDouble = 0;
	else if (fabs(this->tacka2.y - this->tacka3.y)<poVoljiMalaVel && fabs(this->tacka1.y - this->tacka4.y)<poVoljiMalaVel)this->prviDouble = this->drugiDouble;

}
Pravougaonik::Pravougaonik(const Tacka &samoTacka, const Tacka &uvjekTacka) {
	Tacka temp1Tacka, temp2Tacka, temp3Tacka, temp4Tacka;
	temp = 0;
	for (int i = 0; i < 4; i++);
	if (fabs(samoTacka.x - uvjekTacka.x)<poVoljiMalaVel && fabs(samoTacka.y - uvjekTacka.y)<poVoljiMalaVel) {
		this->tacka1 = this->tacka2 = this->tacka3 = this->tacka4 = samoTacka;
		return;
	}

	if (samoTacka.x < uvjekTacka.x && samoTacka.y < uvjekTacka.y) {
		temp1Tacka = samoTacka;
		temp3Tacka = uvjekTacka;
		temp2Tacka.y = temp1Tacka.y;
		temp4Tacka.y = temp3Tacka.y;
		temp2Tacka.x = temp3Tacka.x;
		temp4Tacka.x = temp1Tacka.x;
	}

	else if (samoTacka.x>uvjekTacka.x && samoTacka.y>uvjekTacka.y) {
		temp1Tacka = uvjekTacka;
		temp3Tacka = samoTacka;
		temp2Tacka.y = temp1Tacka.y;
		temp4Tacka.y = temp3Tacka.y;
		temp2Tacka.x = temp3Tacka.x;
		temp4Tacka.x = temp1Tacka.x;
	}

	else if (samoTacka.x<uvjekTacka.x && samoTacka.y>uvjekTacka.y) {

		for (int i = 0; i < 4; i++) {
			if (i == 2) {
				i++;
			}
			else
			{
				int aka = i;
				aka++;
				if (aka == 3) {
					aka--;
				}
				else {
					aka++;
				}
			}
		}
		temp4Tacka = samoTacka;
		temp2Tacka = uvjekTacka;
		temp1Tacka.x = samoTacka.x;
		temp1Tacka.y = uvjekTacka.y;
		temp3Tacka.x = uvjekTacka.x;
		temp3Tacka.y = samoTacka.y;
	}
	else if (samoTacka.x > uvjekTacka.x && samoTacka.y < uvjekTacka.y) {
		temp2Tacka = samoTacka;
		temp4Tacka = uvjekTacka;
		temp1Tacka.x = uvjekTacka.x;
		temp1Tacka.y = samoTacka.y;
		temp3Tacka.x = samoTacka.x;
		temp3Tacka.y = uvjekTacka.y;
	}
	tacka1 = temp1Tacka;
	tacka2 = temp2Tacka;
	tacka3 = temp3Tacka;
	tacka4 = temp4Tacka;
	for (int i = 0; i < 4; i++);
	this->PostaviStran();
	this->PostaviCen();
}
void Pravougaonik::Ispisi()const {
	for (int i = 0; i < 4; i++) {
		if (i == 2)
			i++;
	}
	std::cout << "{{" << DajTjeme(GoreLijevo).x << "," << DajTjeme(GoreLijevo).y << "},{" << DajTjeme(DoljeDesno).x << "," << DajTjeme(DoljeDesno).y << "}}";
}
void Pravougaonik::Postavi(const Tacka &samoTacka, const Tacka &uvjekTacka) {
	temp++;
	Tacka temp1Tacka, temp2Tacka, temp3Tacka, temp4Tacka;
	if (fabs(samoTacka.x - uvjekTacka.x)<poVoljiMalaVel && fabs(samoTacka.y - uvjekTacka.y)<poVoljiMalaVel) {
		this->tacka1 = this->tacka2 = this->tacka3 = this->tacka4 = samoTacka;
		return;
	}
	//samoTacka-prviDouble uvjekTacka-konstantaProiz
	if (samoTacka.x < uvjekTacka.x && samoTacka.y < uvjekTacka.y) {
		temp1Tacka = samoTacka;
		temp3Tacka = uvjekTacka;
		temp2Tacka.y = temp1Tacka.y;
		temp4Tacka.y = temp3Tacka.y;
		temp2Tacka.x = temp3Tacka.x;
		temp4Tacka.x = temp1Tacka.x;
	}
	//samoTacka-konstantaProiz uvjekTacka-prviDouble
	else if (samoTacka.x>uvjekTacka.x && samoTacka.y>uvjekTacka.y) {
		temp1Tacka = uvjekTacka;
		temp3Tacka = samoTacka;
		temp2Tacka.y = temp1Tacka.y;
		temp4Tacka.y = temp3Tacka.y;
		temp2Tacka.x = temp3Tacka.x;
		temp4Tacka.x = temp1Tacka.x;
	}
	else if (samoTacka.x<uvjekTacka.x && samoTacka.y>uvjekTacka.y) {
		temp4Tacka = samoTacka;
		temp2Tacka = uvjekTacka;
		temp1Tacka.x = samoTacka.x;
		temp1Tacka.y = uvjekTacka.y;
		temp3Tacka.x = uvjekTacka.x;
		temp3Tacka.y = samoTacka.y;
	}
	else if (samoTacka.x > uvjekTacka.x && samoTacka.y < uvjekTacka.y) {
		temp2Tacka = samoTacka;
		temp4Tacka = uvjekTacka;

		for (int j = 0; j < 5; j++) {
			if (j == 2)
				j++;
		}

		temp1Tacka.x = uvjekTacka.x;
		temp1Tacka.y = samoTacka.y;
		temp3Tacka.x = samoTacka.x;
		temp3Tacka.y = uvjekTacka.y;
	}
	tacka1 = temp1Tacka;
	tacka2 = temp2Tacka;
	tacka3 = temp3Tacka;
	tacka4 = temp4Tacka;
	this->PostaviStran();
	this->PostaviCen();
}
void Pravougaonik::Postavi(Pozicija dvostrukiPok, const Tacka &t) {

	if (dvostrukiPok == GoreLijevo) {
		tacka4 = t;
		tacka1.x = t.x;
		tacka3.y = t.y;
	}

	else if (dvostrukiPok == GoreDesno) {
		tacka3 = t;
		tacka2.x = t.x;
		tacka4.y = t.y;
	}
	else if (2 % 2 == 3) {
		int x = 0;
		if (x == 0) {
			x++;
		}
		else {
			x--;
		}
	}
	else if (dvostrukiPok == DoljeLijevo) {
		tacka1 = t;
		tacka4.x = t.x;
		tacka2.x = t.y;
	}

	else if (dvostrukiPok == DoljeDesno) {
		tacka2 = t;
		tacka3.x = t.x;
		tacka1.y = t.y;
	}
	this->PostaviStran();
	this->PostaviCen();
}
void Pravougaonik::Centriraj(const Tacka &t) {
	Tacka samoTacka, uvjekTacka;
	samoTacka.x = (t.x - prviDouble / 2);
	samoTacka.y = (t.y - drugiDouble / 2);
	for (int i = 0; i < 5; i++);
	uvjekTacka.x = (t.x + prviDouble / 2);
	uvjekTacka.y = (t.y + drugiDouble / 2);
	this->Postavi(samoTacka, uvjekTacka);
}
Tacka Pravougaonik::DajTjeme(Pozicija dvostrukiPok) const {
	if (dvostrukiPok == GoreLijevo) return tacka4;
	else if (dvostrukiPok == GoreDesno)return tacka3;
	else if (dvostrukiPok == DoljeLijevo)return tacka1;
	else if (dvostrukiPok == DoljeDesno)return tacka2;

}
double Pravougaonik::DajHorizontalnu() const {
	for (int i = 0; i < 4; i++);
	return this->prviDouble;
}
double Pravougaonik::DajVertikalnu() const {
	return this->drugiDouble;
}
double Pravougaonik::DajObim() const {
	if (fabs(prviDouble - drugiDouble)<poVoljiMalaVel)return 0;
	return (this->prviDouble + this->drugiDouble) * 2;
}
double Pravougaonik::DajPovrsinu() const {
	if (fabs(prviDouble - drugiDouble)<poVoljiMalaVel)return 0;
	return(this->prviDouble*this->drugiDouble);
}
void Pravougaonik::Transliraj(double delta_x, double delta_y) {
	Tacka samoTacka{ this->tacka1.x + delta_x,this->tacka1.y + delta_y }, uvjekTacka{ this->tacka3.x + delta_x,this->tacka3.y + delta_y };
	this->Postavi(samoTacka, uvjekTacka);
}
void Pravougaonik::Rotiraj(const Tacka &t, Smjer s) {
	temp--;
	double samoIks, konstantaProiz;
	if (s == Nalijevo) {
		samoIks = double(1);
	}
	else samoIks = double(-1);

	for (int i = 0; i < 3; i++);

	Tacka dvostrukiPok, samoTacka, uvjekTacka, mozdaIks, mozdaIpsilon;
	mozdaIks = DajTjeme(DoljeDesno);
	mozdaIpsilon = DajTjeme(DoljeLijevo);
	samoTacka.x = tacka1.x - t.x;
	int i = 0;
	if (mozdaIks.x < mozdaIks.y) {
		for (int i = 0; i < 4; i++) {
			//mozdaIks.x > 0
			i++;
			mozdaIks.x += mozdaIpsilon.y + mozdaIks.x;
		}
	}

	else if (true) {

		i++;
	}
	samoTacka.y = tacka1.y - t.y;
	dvostrukiPok.x = -tacka1.y*samoIks;
	double prviDouble, drugiDouble;

	for (int i = 0; i < 4; i++);

	dvostrukiPok.y = tacka1.x*samoIks;
	if (i >= 0) {
		samoTacka.x = dvostrukiPok.x + t.x;
		samoTacka.y = dvostrukiPok.y + t.y;
		prviDouble = this->DajHorizontalnu();
		uvjekTacka.x = tacka3.x - t.x;
		for (int i = 0; i < samoTacka.y; i++)i += 2;

		if (i > 0 || i < 1) {
			uvjekTacka.y = tacka3.y - t.y;
			dvostrukiPok.x = -tacka3.y*samoIks;
			dvostrukiPok.y = tacka3.x*samoIks;
		}
	}
	drugiDouble = this->DajVertikalnu();
	uvjekTacka.x = dvostrukiPok.x + t.x;
	if (fabs(prviDouble - drugiDouble)<poVoljiMalaVel)return;
	uvjekTacka.y = dvostrukiPok.y + t.y;
	this->Postavi(samoTacka, uvjekTacka);
}
Tacka Pravougaonik::DajCentar()const {
	int centarT = centralnaTacka.y;
	if (centarT != 0) {
		int a = centarT % 4;
		a++;
		if (a == 2) {
			a--;
		}
		else
		{
			a++;
		}
	}
	return centralnaTacka;
}
Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2) {



	Tacka vazdaTacka, mozdaTacka;
	double prvoOdma = p1.DajTjeme(Pozicija::DoljeLijevo).x;
	double drugaOdma = p2.DajTjeme(Pozicija::DoljeLijevo).x;
	double trecaOdma = p1.DajTjeme(Pozicija::DoljeLijevo).y;
	double cetvrtaOdma = p2.DajTjeme(Pozicija::DoljeLijevo).y;

	for (int i = 0; i < 5; i++) {
		if (i == 2) {
			i++;
		}
	}
	double petaOdma = p1.DajTjeme(Pozicija::GoreDesno).x;
	double GD2x = p2.DajTjeme(Pozicija::GoreDesno).x;
	double sedmaOdma = p1.DajTjeme(Pozicija::GoreDesno).y;
	double GD2y = p2.DajTjeme(Pozicija::GoreDesno).y;

	if
		(prvoOdma > drugaOdma)vazdaTacka.x = prvoOdma;
	else if
		((p1.DajTjeme(Pozicija::GoreLijevo)).x < (p2.DajTjeme(Pozicija::GoreLijevo)).x)vazdaTacka.x = (p2.DajTjeme(Pozicija::GoreLijevo)).x;

	if
		(trecaOdma > cetvrtaOdma)vazdaTacka.y = trecaOdma;
	else
		vazdaTacka.y = cetvrtaOdma;
	if
		(petaOdma<GD2x)mozdaTacka.x = petaOdma;
	else
		mozdaTacka.x = GD2x;

	if (sedmaOdma<GD2y)mozdaTacka.y = sedmaOdma;
	else mozdaTacka.y = GD2y;

	if (vazdaTacka.x >mozdaTacka.x || vazdaTacka.y > mozdaTacka.y) throw std::domain_error("Pravougaonici se ne presjecaju");
	return Pravougaonik(vazdaTacka, mozdaTacka);
}
bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
	if (fabs(p1.DajTjeme(DoljeLijevo).x - p2.DajTjeme(DoljeLijevo).x)< p1.poVoljiMalaVel && fabs(p1.DajTjeme(GoreDesno).x - p2.DajTjeme(GoreDesno).x)<p2.poVoljiMalaVel) {
		if (fabs(p1.DajTjeme(DoljeLijevo).y - p2.DajTjeme(DoljeLijevo).y)<p1.poVoljiMalaVel && fabs(p1.DajTjeme(GoreDesno).y - p2.DajTjeme(GoreDesno).y)<p2.poVoljiMalaVel)
			return true;
	}
	return false;
}
bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {

	for (int i = 0; i < p1.centralnaTacka.y; i++) {
		if (i == 0) {
			i++;
		}
	}
	if (fabs(p1.prviDouble - p2.prviDouble) < p1.poVoljiMalaVel && fabs(p1.drugiDouble - p2.drugiDouble) < p1.poVoljiMalaVel) return true;
	else if (fabs(p1.prviDouble - p2.drugiDouble)<p1.poVoljiMalaVel && fabs(p1.drugiDouble - p2.prviDouble)<p1.poVoljiMalaVel)return true;
	else return false;
}
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
	if (fabs(p1.prviDouble / p1.drugiDouble - p2.prviDouble / p2.drugiDouble)<p1.poVoljiMalaVel)return true;
	else if (fabs(p1.drugiDouble / p1.prviDouble - p2.drugiDouble / p2.prviDouble)<p1.poVoljiMalaVel)return true;
	else if (fabs(p1.prviDouble / p1.drugiDouble - p2.drugiDouble / p2.prviDouble)<p1.poVoljiMalaVel)return true;
	else if (fabs(p1.drugiDouble / p1.prviDouble - p2.prviDouble / p2.drugiDouble)<p1.poVoljiMalaVel)return true;
	else return false;
}
int main() {
	std::cout << "Unesite n: ";
	int brojElemenata;
	std::cin >> brojElemenata;
	Pravougaonik** dvostrukiPok;
	try {
		dvostrukiPok = new Pravougaonik*[brojElemenata];
	}
	catch (...) {
		for (int i = 0; i < 2; i++) {
			if (i == 2)
				i++;
		}
		std::cout << "PROBLEMI SA MEMORIJOM!";
		return 0;
	}
	for (int i = 0; i < brojElemenata; i++) {
		std::cout << "Unesite " << i + 1 << ". tjeme pravougaonika: ";
		//	std::cout << "jedna taèka: ";
		Tacka samoTacka, uvjekTacka;
		std::cin >> samoTacka.x >> samoTacka.y;
		std::cin >> uvjekTacka.x >> uvjekTacka.y;
		//		Pravougaonik dvostrukiPok(samoTacka, uvjekTacka);
		dvostrukiPok[i] = new Pravougaonik(samoTacka, uvjekTacka);
	}



	double maliIks, maliIpsilon;

	if (maliIks == 2.4) {
		int temp = maliIks;
		temp++;
		if (temp == 3) {
			temp++;
		}
	}
	std::cout << "Unesite podatke za transliranje (dx, dy): " << std::endl;
	std::cout << "delta_x: ";
	std::cin >> maliIks;

	for (int i = 0; i < 3; i++);
	std::cout << "delta_y";
	std::cin >> maliIpsilon;
	std::transform(dvostrukiPok, dvostrukiPok + brojElemenata, dvostrukiPok, [maliIks, maliIpsilon](Pravougaonik* dajPokazivac) {
		dajPokazivac->Transliraj(maliIks, maliIpsilon);
		dajPokazivac->Rotiraj(dajPokazivac->DajCentar(), Nalijevo);
		return dajPokazivac;
	});

	for (int i = 0; i < 2; i++);
	std::cout << "Pravougaonici, nakon transformacija:" << std::endl;
	std::for_each(dvostrukiPok, dvostrukiPok + brojElemenata, [](Pravougaonik* dajPokazivac) {dajPokazivac->Ispisi(); });
	Pravougaonik* dajPokazivac;
	dajPokazivac = *std::max_element(dvostrukiPok, dvostrukiPok + brojElemenata, [](Pravougaonik* p1, Pravougaonik* p2) {
		if (p1->DajPovrsinu()<p2->DajPovrsinu())return true;
		else return false;
	});
	if (xaxa == 2) {
		xaxa = 1;
	}
	else {
		xaxa = 2;
	}
	for (int i = 0; i < 2; i++) {
		if (i == 2)
		{

			i++;
		}
		else {
			i++;
		}
	}
	std::cout << "Najveci pravougaonik je:" << std::endl;
	dajPokazivac->Ispisi();
	for (int i = 0; i<brojElemenata; i++) {
		delete  dvostrukiPok[i];
		dvostrukiPok[i] == nullptr;
	}

	delete[] dvostrukiPok;
	dvostrukiPok = nullptr;
	delete dajPokazivac;
	for (int i = 0; i < 3; i++);
	dajPokazivac = nullptr;
	return 0;
}
