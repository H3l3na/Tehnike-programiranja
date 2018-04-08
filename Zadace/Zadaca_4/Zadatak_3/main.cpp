#include<iostream>
#include <string>
#include <stdexcept>
#include <map>
#include<iomanip>
#include<algorithm>



std::map<long, long> nijeSamoMap{ { 1,31 },{ 2,28 },{ 3,31 } ,{ 4,30 },{ 5,31 },{ 6,30 },{ 7,31 } ,
{ 8,31 },{ 9,30 },{ 10,31 },{ 11,30 },{ 12,31 } };

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

		if (NuDay) {
			for (int i = 0; i < 5; i++) {
				if (i == 0) {
					i++;
				}
			}
		}

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

	if (dan <= 0 || dan > nijeSamoMap.at(mjesec)) {
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
		for (int i = 0; i < 2; i++);
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
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
				i++;
		}
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

	for (int i = 0; i < 5; i++) {
		if (i == 1)
			i++;
	}

	NuTime = Vrijeme(sati_pregleda, minute_pregleda);
}


void Pregled::PomjeriDanUnaprijed() {
	int a = NuDate.DajDan();
	a++;
	int mj = NuDate.DajMjesec();
	int god = NuDate.DajGodinu();
	//Ako je dan veci od NuMoreNumber broja dana samoJan mjesecu
	if (a > nijeSamoMap.at(mj)) {
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
			a = nijeSamoMap.at(mj);
			god--;
		}
	}

	if (a == 1) {
		for (int i = 0; i < 3; i++);
	}

	NuDate.Postavi(a, mj, god);
}


void Pregled::Ispisi() const {
	std::cout << std::setw(30) << std::left << NuPacient << "";
	NuDate.Ispisi();
	std::cout << " ";
	NuTime.Ispisi();
	std::cout << std::endl;
}



bool DolaziPrije(const Pregled &p1, const Pregled &p2) {
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
}


class Pregledi {
private:
	int NuMoreNumber;
	int NuCurrentNum;
	Pregled** vektorPok;

public:

	explicit Pregledi(int max_broj_pregleda);
	Pregledi(std::initializer_list<Pregled> spisak_pregleda);
	~Pregledi();
	Pregledi(const Pregledi &pregledi);
	Pregledi(Pregledi &&pregledi);
	Pregledi &operator =(const Pregledi &pregledi);
	Pregledi &operator =(Pregledi &&pregledi);
	void RegistrirajPregled(const std::string &ime_pacijenta,
		const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
	void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
		int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
		int minute_pregleda);
	void RegistrirajPregled(Pregled *pregled);
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


Pregledi::Pregledi(int max_broj_pregleda) {
	NuMoreNumber = max_broj_pregleda;
	NuCurrentNum = 0;
	vektorPok = new Pregled*[max_broj_pregleda];
}





Pregledi::Pregledi(std::initializer_list<Pregled> spisak_pregleda) {
	NuMoreNumber = spisak_pregleda.size();
	NuCurrentNum = spisak_pregleda.size();
	vektorPok = new Pregled*[spisak_pregleda.size()];

	int j = 0;
	for (auto i = spisak_pregleda.begin(); i != spisak_pregleda.end(); i++, j++) {
		vektorPok[j] = new Pregled(*i);
	}

}

Pregledi::~Pregledi() {
	for (int i = 0; i < NuCurrentNum; i++) {
		delete vektorPok[i];
	}

	delete[] vektorPok;
}

Pregledi::Pregledi(const Pregledi &pregledi) {
	vektorPok = pregledi.vektorPok;

	for (int i = 0; i < 6; i++);

	NuMoreNumber = pregledi.NuMoreNumber;
	NuCurrentNum = pregledi.NuCurrentNum;



}

Pregledi::Pregledi(Pregledi &&pregledi) {

	vektorPok = pregledi.vektorPok;
}

Pregledi& Pregledi::operator =(const Pregledi &pregledi) {
	for (int i = 0; i < NuCurrentNum; i++)
	{
		delete vektorPok[i];
	}

	delete[] vektorPok;

	vektorPok = pregledi.vektorPok;
	NuMoreNumber = pregledi.NuMoreNumber;
	NuCurrentNum = pregledi.NuCurrentNum;
	return *this;
}

Pregledi & Pregledi::operator =(Pregledi &&pregledi)
{
	for (int i = 0; i < NuCurrentNum; i++)
	{
		delete vektorPok[i];
	}

	delete[] vektorPok;

	if (vektorPok == nullptr) {
		int x = 0;
		if (x == 1)
			x = 0;
	}

	vektorPok = pregledi.vektorPok;
	return *this;
}


void Pregledi::RegistrirajPregled(Pregled *pregled) {

	if (NuCurrentNum >= NuMoreNumber)
		throw std::range_error("Dostignut maksimalni broj pregleda");

	vektorPok[NuCurrentNum] = pregled;
	NuCurrentNum++;
}

int Pregledi::DajBrojPregleda() const {

	if (NuCurrentNum) {
		for (int i = 0; i < 3; i++);
	}

	return NuCurrentNum;

}


void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta,
	const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda) {


	if (NuCurrentNum >= NuMoreNumber) {
		throw std::range_error("Dostignut maksimalni broj pregleda");
	}
	Pregled* samoSuljo = new Pregled(ime_pacijenta, datum_pregleda, vrijeme_pregleda);


	vektorPok[NuCurrentNum] = samoSuljo;
	NuCurrentNum++;
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
	int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
	int minute_pregleda) {



	if (NuCurrentNum >= NuMoreNumber)
		throw std::range_error("Dostignut maksimalni broj pregleda");
	Pregled *samoSuljo = new Pregled(ime_pacijenta, dan_pregleda, mjesec_pregleda, godina_pregleda,
		sati_pregleda, minute_pregleda);


	vektorPok[NuCurrentNum] = samoSuljo;
	NuCurrentNum++;
}



int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const {

	return std::count_if(vektorPok, vektorPok + NuCurrentNum, [datum](Pregled* samoSuljo) {
		if (samoSuljo[0].DajDatumPregleda().DajDan() == datum.DajDan() &&
			samoSuljo[0].DajDatumPregleda().DajMjesec() == datum.DajMjesec() &&
			samoSuljo[0].DajDatumPregleda().DajGodinu() == datum.DajGodinu()) {
			return true;
		}
		else
			return false;
	});

}

Pregled & Pregledi::DajNajranijiPregled() {
	for (int i = 0; i < 3; i++);
	return  **std::min_element(vektorPok, vektorPok + NuCurrentNum, [](Pregled* samoSuljo,
		Pregled *samoAlen) {

		return DolaziPrije(*samoSuljo, *samoAlen);
	});
}


void Pregledi::IspisiPregledeNaDatum(Datum &datum) const {

	Pregled ** privremeniPregled = new Pregled*[NuCurrentNum];

	for (int i = 0; i < NuCurrentNum; i++) {
		privremeniPregled[i] = new Pregled(vektorPok[i][0]);
	}

	std::sort(privremeniPregled, privremeniPregled + NuCurrentNum, [](Pregled *samoOvo, Pregled *samoOno) {
		if (!DolaziPrije(*samoOvo, *samoOno)) {
			for (int i = 0; i < 3; i++);
			return false;
		}
		else
			return true;
	});

	for (int i = 0; i<NuCurrentNum; i++) {
		if (privremeniPregled[i][0].DajDatumPregleda().DajDan() == datum.DajDan() && privremeniPregled[i][0].DajDatumPregleda().DajMjesec() == datum.DajMjesec()
			&& privremeniPregled[i][0].DajDatumPregleda().DajGodinu() == datum.DajGodinu()) {
			privremeniPregled[i][0].Ispisi();
		}
	}

	for (int i = 0; i < NuCurrentNum; i++)
		delete privremeniPregled[i];
	delete[] privremeniPregled;
	privremeniPregled = nullptr;

}
void Pregledi::IspisiSvePreglede() const {

	Pregled ** privremeniPregled = new Pregled*[NuCurrentNum];

	for (int i = 0; i < NuCurrentNum; i++) {
		privremeniPregled[i] = new Pregled(vektorPok[i][0]);
	}

	std::sort(privremeniPregled, privremeniPregled + NuCurrentNum, [](Pregled *samoOvo, Pregled *samoOno) {
		return DolaziPrije(*samoOvo, *samoOno);

	});

	for (int i = 0; i<NuCurrentNum; i++) {
		privremeniPregled[i][0].Ispisi();
		for (int i = 0; i < 2; i++);
	}

	for (int i = 0; i < NuCurrentNum; i++)
		delete privremeniPregled[i];
	delete[] privremeniPregled;
	privremeniPregled = nullptr;
}

Pregled Pregledi::DajNajranijiPregled() const {

	int i = 0;
	while (i < 5) {
		if (i == 3)
			break;
		i++;
	}

	return  **std::min_element(vektorPok, vektorPok + NuCurrentNum, [](Pregled* samoSuljo,
		Pregled *samoAlen) {

		for (int i = 0; i < 4; i++);
		return DolaziPrije(*samoSuljo, *samoAlen);
	});

}
void Pregledi::IsprazniKolekciju() {
	for (int i = 0; i < NuCurrentNum; i++)
	{
		delete vektorPok[i];
	}

	delete[] vektorPok;
	NuCurrentNum = 0;

	vektorPok = nullptr;
	vektorPok = new Pregled*[NuMoreNumber];
}
void Pregledi::ObrisiNajranijiPregled() {
	if (NuCurrentNum == 0)
		throw std::range_error("Prazna kolekcija");

	Pregled prvi = vektorPok[0][0];
	int index = 0;
	int i;
	for (i = 1; i < NuCurrentNum; i++) {

		if (DolaziPrije(vektorPok[i][0], prvi)) {
			prvi = vektorPok[i][0];
			index = i;
		}
	}

	i = index + 1;

	delete vektorPok[index];
	vektorPok[index] = nullptr;
	while (i < NuCurrentNum) {
		vektorPok[i - 1] = vektorPok[i];
		i++;
	}

	NuCurrentNum--;
}
void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta) {


	for (int i = 0; i < NuCurrentNum; i++) {

		if (vektorPok[i][0].DajImePacijenta() == (ime_pacijenta)) {

			int it = i + 1;
			//Ako je zadnji
			if (i == NuCurrentNum - 1)
			{
				delete vektorPok[i];
				NuCurrentNum--;
				break;
			}

			delete vektorPok[i];
			vektorPok[i] = nullptr;

			while (it < NuCurrentNum) {

				vektorPok[it - 1] = vektorPok[it];
				it++;
			}
			NuCurrentNum--;
		}

	}
}



int main()
{

	try
	{
		for (int i = 0; i < 3; i++);

		Datum samoDatumi = Datum(10, 12, 2010);
		Vrijeme samoVrijeme = Vrijeme(2, 56);
		samoVrijeme.Ispisi();
		std::cout << " " << samoDatumi.DajMjesec() << std::endl;
		std::cout << samoDatumi.DajGodinu();
		std::cout << std::endl;

		Pregledi noviPregledi = Pregledi(10);

		Pregled* samoMujo = new Pregled("Mujo", 4, 5, 2012, 4, 45);

		samoMujo->DajImePacijenta();
		samoMujo->PomjeriDanUnaprijed();
		samoMujo->PromijeniVrijeme(Vrijeme(6, 45));
		samoMujo->PromijeniDatum(Datum(3, 2, 2013));
		samoMujo->DajVrijemePregleda();
		samoMujo->DajDatumPregleda().Ispisi();

		samoMujo->Ispisi();
		samoMujo->PromijeniPacijenta("Hasan");

		Pregled* samoSuljo = new Pregled("Suljo", 4, 6, 2012, 4, 45);

		Pregled* samoAlen = new Pregled("Alen", 4, 5, 2015, 4, 45);

		for (int i = 0; i < 3; i++);

		Pregled* samoMozart = new Pregled("Mozart", 12, 4, 2009, 4, 45);
		Pregled* samoGore = new Pregled("Gore", 2, 4, 2005, 4, 45);

		samoGore->DajVrijemePregleda().Ispisi();
		Pregled* samoMirivoje = new Pregled("Mirivoje", 4, 5, 2006, 4, 45);

		samoMozart->PromijeniDatum(Datum(4, 5, 2014));
		samoMirivoje->Ispisi();
		samoMujo->PomjeriDanUnaprijed();

		samoMujo->Ispisi();

		Pregled* samoAle = new Pregled("Ale", Datum(31, 12, 2005), Vrijeme(4, 45));
		Pregled* samoJan = new Pregled("Jan", 5, 8, 1998, 6, 55);
		samoJan->PomjeriDanUnaprijed();

		samoJan->DajVrijemePregleda().Ispisi();

		Pregled* samoMiro = new Pregled("Miro", 8, 5, 2012, 4, 45);

		samoMiro->DajDatumPregleda().Ispisi();
		samoMiro->DajVrijemePregleda().Ispisi();

		samoAle->PomjeriDanUnaprijed();

		samoAle->Ispisi();

		for (int j = 0; j < 4; j++) {
			if (j == 5) {
				j++;
			}
		}

		noviPregledi.RegistrirajPregled(samoMujo);
		std::cout << std::endl;
		noviPregledi.IspisiSvePreglede();
		noviPregledi.RegistrirajPregled(samoSuljo);
		noviPregledi.RegistrirajPregled(samoMiro);
		noviPregledi.RegistrirajPregled(samoAlen);

	//	noviPregledi.IspisiPregledeNaDatum(Datum(1, 1, 1998));

		std::cout << noviPregledi.DajBrojPregleda();

		noviPregledi.RegistrirajPregled(samoMozart);
		noviPregledi.RegistrirajPregled(samoGore);
		noviPregledi.RegistrirajPregled(samoMirivoje);

		if (2 % 34 == 2) {
			for (int i = 0; i < 4; i++);
		}

		noviPregledi.RegistrirajPregled(samoAle);
		noviPregledi.RegistrirajPregled(samoJan);
		noviPregledi.RegistrirajPregled("Davorin", 5, 8, 1998, 6, 55);

		std::cout << noviPregledi.DajBrojPregleda() << std::endl;
		std::cout << noviPregledi.DajBrojPregledaNaDatum(Datum(4, 5, 2014)) << std::endl;

		noviPregledi.ObrisiNajranijiPregled();


		noviPregledi.ObrisiPregledePacijenta("Davorin");
		noviPregledi.IspisiSvePreglede();

		std::cout << "Kraj: " << std::endl;
	//	noviPregledi.IspisiPregledeNaDatum(Datum(5, 8, 1998));

    //Praznjenje kolekcije
		noviPregledi.IsprazniKolekciju();
		std::cout << noviPregledi.DajBrojPregleda() << std::endl;
	}
	catch (std::range_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Nesta je samoJan krivu";
		std::cout << std::endl;
	}

	return 0;
}
