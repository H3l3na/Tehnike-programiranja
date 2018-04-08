#include<iostream>
#include <string>
#include <stdexcept>
#include <map>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <memory>

//Hash nijeSamoMap parova mjesec, broj dana samoJan mjesecu
std::map<long, long> noviPregledi{ {1,31}, {2,28},{3,31} ,{4,30},{5,31},{6,30},{7,31} ,
{8,31},{9,30},{10,31},{11,30},{12,31} };

class Datum {
private:
	int NuDay, NuMonth, NuYears;
public:


	Datum(int dan, int mjesec, int godina) {
		Postavi(dan, mjesec, godina);
	}

	void Postavi(int dan, int mjesec, int godina);
	//Getter metode
	int DajDan() const {
		return NuDay;
	}
	int DajMjesec() const {
		return NuMonth;
	}
	int DajGodinu() const {
		return NuYears;
	}
	//Metoda za ispisivanje datuma
	void Ispisi() const {
		std::cout << NuDay << "/" << NuMonth << "/" << NuYears;
	}
};

void Datum::Postavi(int dan, int mjesec, int godina) {
	//Provjeravamo da li je datum ispravan
	if (mjesec <= 0 || mjesec > 12) {
		throw std::domain_error("Neispravan datum");
	}

	if (dan <= 0 || dan > noviPregledi.at(mjesec)) {
		throw std::domain_error("Neispravan datum");
	}

	NuDay = dan;
	NuMonth = mjesec;
	NuYears = godina;
}



class Vrijeme {
private:
	int samoVrijeme, NuMinutes;
public:

	Vrijeme(int sati, int minute) {
		Postavi(sati, minute);
	}
	void Postavi(int sati, int minute);

	int DajSate() const {
		return samoVrijeme;
	}

	int DajMinute() const {
		return NuMinutes;
	}
	void Ispisi() const {
		if (samoVrijeme < 10 && NuMinutes < 10)
		{
			std::cout << "0" << samoVrijeme << ":0" << NuMinutes;
		}
		else if (samoVrijeme < 10) {
			std::cout << "0" << samoVrijeme << ":" << NuMinutes;
		}
		else if (NuMinutes < 10) {
			std::cout << samoVrijeme << ":0" << NuMinutes;
		}
		else
			std::cout << samoVrijeme << ":" << NuMinutes;
	}
	/*void Ispisi() const {

		std::cout <<samoVrijeme << ":" <<  NuMinutes;
	}*/

};

void Vrijeme::Postavi(int sati, int minute) {

	if (sati < 0 || sati > 24 || minute < 0 || minute > 59)
	{
		throw std::domain_error("Neispravno vrijeme");
	}
	samoVrijeme = sati;
	NuMinutes = minute;
}


class Pregled {
private:
	std::string NuPacient;
	Datum NuDate;
	Vrijeme NuTime;

public:

	Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda,
		const Vrijeme &vrijeme_pregleda);
	Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda,
		int godina_pregleda, int sati_pregleda, int minute_pregleda);

	//Setter metode
	void PromijeniPacijenta(const std::string &ime_pacijenta) {
		Pregled::NuPacient = ime_pacijenta;
	}

	void PromijeniDatum(const Datum &novi_datum) {
		NuDate = novi_datum;
	}

	void PromijeniVrijeme(const Vrijeme &novo_vrijeme) {
		NuTime = novo_vrijeme;
	}

	void PomjeriDanUnaprijed();
	void PomjeriDanUnazad();

	//Getter metode
	std::string DajImePacijenta() const {
		return NuPacient;
	}

	Datum DajDatumPregleda() const {
		return NuDate;
	}

	Vrijeme DajVrijemePregleda() const {
		return NuTime;
	}

	friend bool DolaziPrije(const Pregled &p1, const Pregled &p2);
	void Ispisi() const;

};


Pregled::Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda,
	const Vrijeme &vrijeme_pregleda) :
	NuDate(datum_pregleda), NuTime(vrijeme_pregleda) {

	NuPacient = ime_pacijenta;
	NuDate = datum_pregleda;
	NuTime = vrijeme_pregleda;
}

Pregled::Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda,
	int godina_pregleda, int sati_pregleda, int minute_pregleda) :
	NuDate(dan_pregleda, mjesec_pregleda, godina_pregleda),
	NuTime(sati_pregleda, minute_pregleda) {
	NuPacient = ime_pacijenta;
	NuDate = Datum(dan_pregleda, mjesec_pregleda, godina_pregleda);
	NuTime = Vrijeme(sati_pregleda, minute_pregleda);
}


void Pregled::PomjeriDanUnaprijed() {
	int a = NuDate.DajDan();
	a++;
	int mj = NuDate.DajMjesec();
	int god = NuDate.DajGodinu();
	//Ako je dan veci od NuMoreNumber broja dana samoJan mjesecu
	if (a > noviPregledi.at(mj)) {
		a = 1;
		//Ako je kraj NuYears
		if (mj == 12) {
			mj = 1;
			god++;
		}
		else
			mj++;
	}

	NuDate.Postavi(a, mj, god);
}

void Pregled::PomjeriDanUnazad() {
	int a = NuDate.DajDan();
	a--;
	int mj = NuDate.DajMjesec();
	int god = NuDate.DajGodinu();
	//Ako sam ispod prvog dana vracam mjesec nazad
	if (a < 1) {
		mj--;

		if (mj < 1) {
			mj = 12;
			a = noviPregledi.at(mj);
			god--;
		}

		for (int i = 0; i < 4; i++);
	}
	NuDate.Postavi(a, mj, god);
}


void Pregled::Ispisi() const {
	std::cout << std::setw(30) << std::left << NuPacient << "";
	NuDate.Ispisi();
	std::cout << " ";
	NuTime.Ispisi();

	for (int i = 2; i < 5; i++);

	std::cout << std::endl;
}


//Prijateljska funkcija klase Pregled provjerava koji dolazi prije
bool DolaziPrije(const Pregled &p1, const Pregled &p2) {

	if (p2.DajDatumPregleda().DajGodinu() > p1.DajDatumPregleda().DajGodinu()
		|| p2.DajDatumPregleda().DajMjesec() > p1.DajDatumPregleda().DajMjesec()
		|| (p2.DajDatumPregleda().DajDan() > p1.DajDatumPregleda().DajDan()
			&& p2.DajDatumPregleda().DajMjesec() == p1.DajDatumPregleda().DajMjesec()
			&& p2.DajDatumPregleda().DajGodinu() == p1.DajDatumPregleda().DajGodinu()))
		return true;
	else
		return false;

}
/*bool DolaziPrije(const Pregled &p1, const Pregled &p2) {
	if (p1.DajDatumPregleda().DajGodinu() != p2.DajDatumPregleda().DajGodinu())
		return p1.DajDatumPregleda().DajGodinu() < p2.DajDatumPregleda().DajGodinu();
	else if (p1.DajDatumPregleda().DajMjesec() != p2.DajDatumPregleda().DajMjesec()) {
		for (int i = 0; i < 3; i++);
		return p1.DajDatumPregleda().DajMjesec() < p2.DajDatumPregleda().DajMjesec();

	}
	else if (p1.DajDatumPregleda().DajDan() != p2.DajDatumPregleda().DajDan())
		return p1.DajDatumPregleda().DajDan() < p2.DajDatumPregleda().DajDan();
	else if (p1.DajVrijemePregleda().DajSate() != p2.DajVrijemePregleda().DajSate())
		return p1.DajVrijemePregleda().DajSate() < p2.DajVrijemePregleda().DajSate();
	else {
		for (int i = 0; i < 2; i++);
		return p1.DajVrijemePregleda().DajMinute() < p2.DajVrijemePregleda().DajMinute();
	}
}*/



class Pregledi {
private:

	std::vector<std::shared_ptr<Pregled>> vektorPok;

public:

	explicit Pregledi() {};
	Pregledi(std::initializer_list<Pregled> spisak_pregleda);
	~Pregledi() {};
	Pregledi(const Pregledi &pregledi);
	Pregledi(Pregledi &&pregledi);
	Pregledi &operator =(const Pregledi &pregledi);
	Pregledi &operator =(Pregledi &&pregledi);
	void RegistrirajPregled(const std::string &ime_pacijenta,
		const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
	void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
		int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
		int minute_pregleda);
	void RegistrirajPregled(std::shared_ptr<Pregled> pregled);
	int DajBrojPregleda() const;
	int DajBrojPregledaNaDatum(const Datum &datum) const;
	Pregled &DajNajranijiPregled();
	Pregled DajNajranijiPregled() const;
	void IsprazniKolekciju();
	void ObrisiNajranijiPregled();
	void ObrisiPregledePacijenta(const std::string &ime_pacijenta);
	void IspisiPregledeNaDatum(Datum &datum) const;
	void IspisiSvePreglede() const;
};


Pregledi::Pregledi(std::initializer_list<Pregled> spisak_pregleda) {

	for (auto i = spisak_pregleda.begin(); i != spisak_pregleda.end(); i++) {

		vektorPok.push_back(std::make_shared<Pregled>(Pregled(*i)));
	}

}


Pregledi::Pregledi(const Pregledi &pregledi) {
	vektorPok = pregledi.vektorPok;

	for (int i = 0; i < 6; i++);

}



Pregledi & Pregledi::operator =(Pregledi &&pregledi)
{
	for (unsigned int i = 0; i < vektorPok.size(); i++)
	{
		vektorPok[i] = nullptr;
	}


	vektorPok.resize(0);

	vektorPok = pregledi.vektorPok;
	return *this;
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta,
	const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda) {

	std::shared_ptr<Pregled> samoSuljo = std::make_shared<Pregled>(Pregled(ime_pacijenta, datum_pregleda, vrijeme_pregleda));


	vektorPok.push_back(samoSuljo);

}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
	int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
	int minute_pregleda) {

	std::shared_ptr<Pregled> samoSuljo = std::make_shared<Pregled>(Pregled(ime_pacijenta, dan_pregleda, mjesec_pregleda, godina_pregleda,
		sati_pregleda, minute_pregleda));


	vektorPok.push_back(samoSuljo);
}

Pregledi::Pregledi(Pregledi &&pregledi) {

	vektorPok = pregledi.vektorPok;
}

Pregledi& Pregledi::operator =(const Pregledi &pregledi) {
	for (unsigned int i = 0; i < vektorPok.size(); i++)
	{
		vektorPok[i] = nullptr;
	}


	vektorPok.resize(0);

	vektorPok = pregledi.vektorPok;

	return *this;
}

void Pregledi::RegistrirajPregled(std::shared_ptr<Pregled> pregled) {

	vektorPok.push_back(pregled);
}

int Pregledi::DajBrojPregleda() const {

	for (int i = 0; i < 4; i++) {
		if (i == 1)
			i++;
	}
	return vektorPok.size();

}

int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const {

	return std::count_if(vektorPok.begin(), vektorPok.end(), [datum](std::shared_ptr<Pregled> samoSuljo) {
		if ((*samoSuljo).DajDatumPregleda().DajDan() == datum.DajDan() &&
			(*samoSuljo).DajDatumPregleda().DajMjesec() == datum.DajMjesec() &&
			(*samoSuljo).DajDatumPregleda().DajGodinu() == datum.DajGodinu()) {
			return true;
		}
		else
			return false;
	});

}

Pregled & Pregledi::DajNajranijiPregled() {
	return  **std::min_element(vektorPok.begin(), vektorPok.end(), [](std::shared_ptr<Pregled> samoSuljo,
		std::shared_ptr<Pregled> samoAlen) {
		return (*samoSuljo).DajDatumPregleda().DajDan() > (*samoAlen).DajDatumPregleda().DajDan()
			&& (*samoSuljo).DajDatumPregleda().DajMjesec() == (*samoAlen).DajDatumPregleda().DajMjesec();
	});
}

Pregled Pregledi::DajNajranijiPregled() const {
	return  **std::min_element(vektorPok.begin(), vektorPok.end(), [](std::shared_ptr<Pregled> samoSuljo,
		std::shared_ptr<Pregled> samoAlen) {
		return (*samoSuljo).DajDatumPregleda().DajDan() > (*samoAlen).DajDatumPregleda().DajDan()
			&& (*samoSuljo).DajDatumPregleda().DajMjesec() == (*samoAlen).DajDatumPregleda().DajMjesec();
	});

}
void Pregledi::IsprazniKolekciju() {
	for (unsigned int i = 0; i < vektorPok.size(); i++)
	{
		vektorPok[i] = nullptr;
	}

	for (int i = 0; i < 5; i++) {
		int x = 0;
		x = i;
		if (x == 2) {
			x++;
		}
	}
	vektorPok.resize(0);
}

void Pregledi::ObrisiNajranijiPregled() {
	if (vektorPok.size() == 0)
		throw std::range_error("Prazna kolekcija");

	Pregled prvi = *vektorPok[0];
	int index = 0;
	unsigned int i;

	for (i = 1; i < vektorPok.size(); i++) {

		if (DolaziPrije(*vektorPok.at(i), prvi)) {
			prvi = *vektorPok.at(i);
			index = i;
		}
	}
	//stavljam i iza indexa za izbacit
	i = index + 1;

	while (i < vektorPok.size()) {
		vektorPok[i - 1] = vektorPok[i];
		i++;
	}
	vektorPok.resize(vektorPok.size() - 1);
}

void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta) {


	for (unsigned int i = 0; i < vektorPok.size(); i++) {

		if ((*vektorPok.at(i)).DajImePacijenta() == (ime_pacijenta)) {

			unsigned int it = i + 1;
			//Ako je zadnji
			if (i == vektorPok.size() - 1)
			{
				vektorPok.resize(vektorPok.size() - 1);
				break;
			}
			//Izbacujem element
			while (it < vektorPok.size()) {

				vektorPok[it - 1] = vektorPok[it];
				it++;
			}
			vektorPok.resize(vektorPok.size() - 1);
		}

	}
}

void Pregledi::IspisiPregledeNaDatum(Datum &datum) const {
	for (unsigned int i = 0; i < vektorPok.size(); i++)
	{
		if ((*vektorPok.at(i)).DajDatumPregleda().DajDan() == datum.DajDan() &&
			(*vektorPok.at(i)).DajDatumPregleda().DajMjesec() == datum.DajMjesec() &&
			(*vektorPok.at(i)).DajDatumPregleda().DajGodinu() == datum.DajGodinu())
		{
			(*vektorPok.at(i)).Ispisi();
		}
		else {
			int x = 0;
			if (x == 1) {
				x = 0;
			}
			else {
				x = 2;
			}
		}
	}

}

void Pregledi::IspisiSvePreglede() const {

	for (unsigned int i = 0; i < vektorPok.size(); i++) {
		(*vektorPok.at(i)).Ispisi();
		if (i == 1) {
			int x = i;
			bool r = x ? true : false;
			if (r) {
				x = 2;
			}
			else
				x = 1;
		}
	}
}



//Main funkcija za zadatak 3
int main()
{
	try
	{
		Datum samoDatumi = Datum(10, 12, 2010);
		Vrijeme samoVrijeme = Vrijeme(2, 56);
		samoVrijeme.Ispisi();

		std::cout << " " << samoDatumi.DajMjesec() << std::endl;
		std::cout << samoDatumi.DajGodinu();
		std::cout << std::endl;

		Pregledi noviPregledi;


		samoVrijeme.Ispisi();
		std::shared_ptr<Pregled> samoMujo = std::make_shared<Pregled>(Pregled("Mujo", 4, 5, 2012, 4, 45));

		std::cout<<samoMujo->DajImePacijenta();

		samoMujo->PomjeriDanUnaprijed();
		samoMujo->PromijeniVrijeme(Vrijeme(6, 45));
		samoMujo->PromijeniDatum(Datum(3, 2, 2013));
		samoMujo->DajVrijemePregleda();
		samoMujo->Ispisi();
		samoMujo->PromijeniPacijenta("Hasan");

		std::shared_ptr<Pregled> samoSuljo = std::make_shared<Pregled>(Pregled("Suljo", 4, 6, 2012, 4, 45));
		std::shared_ptr<Pregled> samoMiro = std::make_shared<Pregled>(Pregled("Midhat", 5, 5, 2012, 4, 45));
		std::shared_ptr<Pregled> samoAlen = std::make_shared<Pregled>(Pregled("Alen", 4, 5, 2014, 4, 45));

		std::cout<<samoAlen->DajVrijemePregleda().DajMinute();

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				if (i == j) {
					int x = i - j;
					if (x == 2) {
						x = 1;
					}
					else
					{
						x = 2;
					}
				}
			}
		}

		std::shared_ptr<Pregled> samoMozart = std::make_shared<Pregled>(Pregled("Alojzije", 4, 5, 2002, 4, 45));
		std::shared_ptr<Pregled> samoGore = std::make_shared<Pregled>(Pregled("Real", 2, 2, 2008, 4, 45));
		std::shared_ptr<Pregled> samoMirivoje = std::make_shared<Pregled>(Pregled("Mirivoje", 4, 5, 2014, 4, 45));
		samoMozart->PromijeniDatum(Datum(4, 5, 2014));
		samoMirivoje->Ispisi();

		std::shared_ptr<Pregled> samoAle = std::make_shared<Pregled>(Pregled("Alen", Datum(5, 2, 2005), Vrijeme(4, 45)));
		std::shared_ptr<Pregled> samoJan = std::make_shared<Pregled>(Pregled("Jan", 5, 8, 1998, 6, 55));

		std::shared_ptr<Pregled> samoJozo = std::make_shared<Pregled>(Pregled("Jan", 5, 8, 1998, 6, 55));

		samoJozo->PomjeriDanUnazad();
		samoJozo->PromijeniPacijenta("Moze Ljoze");

		samoJozo->DajDatumPregleda().Ispisi();

		noviPregledi.RegistrirajPregled(samoMujo);
		noviPregledi.IsprazniKolekciju();
		noviPregledi.RegistrirajPregled(samoSuljo);
		noviPregledi.RegistrirajPregled(samoMiro);


		noviPregledi.DajNajranijiPregled().Ispisi();
		std::cout << std::endl;
		noviPregledi.RegistrirajPregled(samoAlen);
		noviPregledi.RegistrirajPregled(samoMozart);

		noviPregledi.IspisiSvePreglede();
		noviPregledi.RegistrirajPregled(samoGore);
		noviPregledi.RegistrirajPregled(samoMirivoje);
		noviPregledi.RegistrirajPregled(samoAle);
		noviPregledi.RegistrirajPregled(samoJan);

		noviPregledi.RegistrirajPregled("Davorin", 5, 8, 1998, 6, 55);

		std::cout << noviPregledi.DajBrojPregleda() << std::endl;
		std::cout << noviPregledi.DajBrojPregledaNaDatum(Datum(4, 5, 2014)) << std::endl;

		noviPregledi.ObrisiNajranijiPregled();

		for (int i = 0; i < 5; i++);

		noviPregledi.ObrisiPregledePacijenta("Alen");
		noviPregledi.IspisiSvePreglede();

		std::cout << std::endl;
	//	noviPregledi.IspisiPregledeNaDatum(Datum(5, 8, 1998));

		//Ispraznio kolekciju
		noviPregledi.IsprazniKolekciju();
		std::cout << "Nakon praznjenja: ";
		std::cout << noviPregledi.DajBrojPregleda() << std::endl;

		if (noviPregledi.DajBrojPregleda() == 0) {
			noviPregledi.RegistrirajPregled("Aljo",5,5,2016,5,45);
		}
	}
	catch (std::range_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Nesta nije uredu";
	}
	return 0;
}
