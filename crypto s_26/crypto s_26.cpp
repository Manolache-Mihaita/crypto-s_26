// crypto s_26.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <map>

//std::map<std::string, int>digrams;
std::vector<std::string>digrams;
void read_digrams_from_file() {
	std::ifstream myfile;
	myfile.open("digrams.txt");
	std::string a;
	while (myfile >> a) {
	//	auto &it = digrams.find(a);
	//	if (it != digrams.end())it->second++;
	//	else digrams.insert(std::make_pair(a, 0));
		for (int i = 0; i < a.size(); i++) {
			a[i] -= 32;
		}
		digrams.push_back(a);
	}
	myfile.close();
}
// std::map<std::string, int>trigrams;
std::vector<std::string>trigrams;
void read_trigrams_from_file() {
	std::ifstream myfile;
	myfile.open("trigrams.txt");
	std::string a;
	while (myfile >> a) {
		//auto &it = trigrams.find(a);
		//if (it != trigrams.end())it->second++;
		//else trigrams.insert(std::make_pair(a, 0));
		for (int i = 0; i < a.size(); i++) {
			a[i] -= 32;
		}
		trigrams.push_back(a);
	}
	myfile.close();
}

std::string read_text_from_file() {
	std::ifstream myfile;
	myfile.open("normal_text.txt");
	std::string a;
	std::string to_return = "";
	while (myfile >> a) {
		to_return += a;
	}
	myfile.close();
	return to_return;
}
std::string enc_key;
void read_enc_key() {
	std::ifstream myfile;
	myfile.open("enc_key.txt");
	std::string a;
	while (myfile >> a)enc_key += a;
	myfile.close();
}
std::string enc_text;
void enc_text_nd_transf(std::string dec_text) {
	for (auto i : dec_text) {
		if (i >= 'A'&&i <= 'Z')enc_text += enc_key[i % 65];
		else if (i >= 'a'&&i <= 'z')enc_text += enc_key[(i - 32) % 65];
	}
}
std::vector<char> single_L_stat;
void read_single_L_stat() {
	std::ifstream myfile;
	myfile.open("single_letter_occurance.txt");
	for (int i = 0; i < 26; i++) {
		char p;
		myfile >> p;
		float r;
		myfile >> r;
		single_L_stat.push_back(p - 32);
	}
}
struct dta_stat {
	char letter;
	int stat;
};
void buuble_svort(std::vector < dta_stat>&vctr) {
	int ok = true;
	while (ok) {
		ok = false;
		for (int i = 0; i < vctr.size() - 1; i++) {
			if (vctr[i].stat < vctr[i + 1].stat) {
				dta_stat p = vctr[i];
				vctr[i] = vctr[i + 1];
				vctr[i + 1] = p;
				ok = true;
			}
		}
	}
}

void ins_ltr_dta_sta_vctr(std::vector<dta_stat>&vctr) {
	for (int i = 0; i < vctr.size(); i++)vctr[i].letter = i + 65;
}
struct v1 {
	char character;
	dta_stat* ptr_fct;
};
struct v2 {
	std::string letter_group;
	int count;
};
std::vector<v1>mke_link_enc_single_L_stat(std::vector<dta_stat>vctr) {
	std::vector<v1>return_vctr;
	for (int i = 0; i < 26; i++) {
		v1 p;
		p.ptr_fct = &vctr[i];
		return_vctr.push_back(p);
	}
	return return_vctr;
}
void link_enc_frec_with_single_list_stat(std::vector<v1>&stat) {
	for (int i = 0; i < stat.size(); i++) {
		stat[i].character = single_L_stat[i];
		char p = stat[i].character;
		stat[i].character = stat[i].ptr_fct->letter;
		stat[i].ptr_fct->letter = p;
	}
}

void buuble_svort_v2_struct(std::vector<v2> &a) {
	bool ok = true;
	while (ok) {
		ok = false;
		for (int i = 0; i < a.size()-1; i++) {
			if (a[i].count < a[i + 1].count) {
				v2 p = a[i];
				a[i] = a[i + 1];
				a[i + 1] = p;
				ok = true;
			}
		}
	}
}


std::map<std::string, int>enc_digrams;
std::vector<v2>vector_digrams;
void get_digrams_from_enc_text() {
	for (int i = 0; i < enc_text.size() - 1; i++) {
		std::string a = "";
		a += enc_text[i];
		a += enc_text[i + 1];
		//a.push_back[enc_text[i]];
		//a.push_back[enc_text[i + 1]];
		auto &it = enc_digrams.find(a);
		if (it == enc_digrams.end())enc_digrams.insert(std::make_pair(a, 1));
		else it->second++;
	}
	for (auto &it : enc_digrams) {
		v2 p;
		p.letter_group = it.first;
		p.count = it.second;
		vector_digrams.push_back(p);
	}

}
std::map<std::string, int>enc_trigrams;
std::vector<v2>vector_trigrams;
void get_trigrams_from_enc_text() {
	for (int i = 0; i < enc_text.size() - 2; i++) {
		std::string a;
		a += enc_text[i];
		a += enc_text[i + 1];
		a += enc_text[i + 2];
		//a.push_back[enc_text[i]];
		//a.push_back[enc_text[i + 1]];
		//a.push_back[enc_text[i + 2]];
		auto &it = enc_trigrams.find(a);
		if (it == enc_trigrams.end())enc_trigrams.insert(std::make_pair(a, 1));
		else it->second++;
	}
	for (auto &it : enc_trigrams) {
		v2 p;
		p.letter_group = it.first;
		p.count = it.second;
		vector_trigrams.push_back(p);
	}
}
void get_statistics_from_file() {
	read_trigrams_from_file();
	read_digrams_from_file();
	read_single_L_stat();
 }
int main()
{
	get_statistics_from_file();
	read_enc_key();
	std::vector<dta_stat> frec_stat(26);
	std::vector<int> enc_frec(26);
	enc_text_nd_transf(read_text_from_file());
	// set the vctr with a,b,c..
	ins_ltr_dta_sta_vctr(frec_stat);

	//put the freq in the vector
	for (int i = 0; i < enc_text.size(); i++) {
		frec_stat[enc_text[i] % 65].stat++;
	}
	std::cout << enc_text.size();
	std::cout << std::endl << std::endl;
	//sort the vector?
	buuble_svort(frec_stat);

	get_digrams_from_enc_text();
	get_trigrams_from_enc_text();
	buuble_svort_v2_struct(vector_digrams);
	buuble_svort_v2_struct(vector_trigrams);
	for (int i = 0; i < frec_stat.size(); i++) {
		std::cout << frec_stat[i].letter << "-->>" << frec_stat[i].stat << std::endl;
	}
	std::map<char, char> decrypt_sgl_letter_stat;
	for (int i = 0; i < 26; i++) {
		decrypt_sgl_letter_stat.insert(std::make_pair(frec_stat[i].letter, single_L_stat[i]));
	}
	/*std::vector<char>decrypt_sgl_letter_stat(26);
	for (int i = 0; i < 26; i++) {
		int j = 0;
		while (frec_stat[j].letter != i + 65)j++;
		decrypt_sgl_letter_stat[i] = single_L_stat[j];
	}*/
	std::cout << std::endl;
	std::cout << std::endl;
	/*for (int i = 0; i < 26; i++) {
		if (enc_key[i] == decrypt_sgl_letter_stat[i])std::cout << 1;
		else std::cout << 0;
	}*/
	int count = 0;
	for (int i = 0; i < 26; i++) {
		auto &it = decrypt_sgl_letter_stat.find(enc_key[i]);
		if (i + 65 == it->second) {
			std::cout << 1;
			count++;
		}
		else std::cout << 0;
	}
	std::cout << std::endl << count;
	//std::cout << enc_text;
	//std::cout << std::endl << enc_text.size();
	std::cout << std::endl << std::endl;
	//std::cout << digrams.size() << "   " << trigrams.size() << std::endl << enc_digrams.size() << "   " << enc_trigrams.size();
	

	return 0;
}
