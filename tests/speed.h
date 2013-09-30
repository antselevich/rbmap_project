#include <iostream>
#include "../rbmap.h"
#include <ctime>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cassert>
#include <string>
#include <fstream>

void midi(int max, int some,
			__int64 *m_ins_time, 
			__int64 *rb_ins_time, 
			__int64 *m_del_time, 
			__int64 *rb_del_time, 
			__int64 *m_ins2_time, 
			__int64 *rb_ins2_time) {
	__int64 begin, time, point;
	std::map<int, int> M;
	rbmap<int, int> N;
	begin = clock();

	std::vector< int > v(max);
	int i = 0;
	int j;
	while (i < max) {
		j = 0;
		while (j < some) {
			v[i] = j;
			i++;
			j++;
		}
	}
	std::random_shuffle( v.begin(), v.end() );

	for (int i = 0; i < max; i++)
	{
		M.insert(std::pair<int,int>(v[i],1));
	}
	*m_ins_time = clock() - begin;
	begin = clock();
	for (int i = 0; i < max; i++)
	{
		N.insert(std::pair<int,int>(v[i],1));
	}

	*rb_ins_time = clock() - begin;

		std::random_shuffle( v.begin(), v.end() );
	
	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		M.erase(v[i]);
		time += (clock()-point);

	}
	*m_del_time = time;

	
	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		N.erase(v[i]);
		time += (clock()-point);
	}
	*rb_del_time = time;

	std::vector<int>::iterator it_some = v.begin();
	for (int i = 0; i < some; i++)
		it_some++;

	std::vector<int>v2(v.begin(), it_some);

	std::random_shuffle( v2.begin(), v2.end() );
	
	begin = clock();
	for (int i = 0; i < v2.size(); i++)
	{
		M.insert(std::pair<int,int>(v2[i],1));
	}
	*m_ins2_time = clock() - begin;

	begin = clock();
	for (int i = 0; i < v2.size(); i++)
	{
		N.insert(std::pair<int,int>(v2[i],1));
	}
	*rb_ins2_time = clock() - begin;

}

void oidi(int max, int some,
			__int64 *m_ins_time, 
			__int64 *rb_ins_time, 
			__int64 *m_del_time, 
			__int64 *rb_del_time, 
			__int64 *m_ins2_time, 
			__int64 *rb_ins2_time) {
	srand(time(0));
	__int64 begin, time, point;
	std::map<int, int> M;
	rbmap<int, int> N;
	begin = clock();
	for (int i = 0; i < max; i++)
	{
		M.insert(std::pair<int,int>(i,1));
	}
	*m_ins_time = clock() - begin;
	begin = clock();
	for (int i = 0; i < max; i++)
	{
		N.insert(std::pair<int,int>(i,1));
	}

	*rb_ins_time = clock() - begin;

	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		M.erase(i);
		time += (clock()-point);

	}
	*m_del_time = time;

	
	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		N.erase(i);
		time += (clock()-point);
	}
	*rb_del_time = time;

	begin = clock();
	for (int i = 0; i < some; i++)
	{
		M.insert(std::pair<int,int>(i,1));
	}
	*m_ins2_time = clock() - begin;

	begin = clock();
	for (int i = 0; i < some; i++)
	{
		N.insert(std::pair<int,int>(i,1));
	}
	*rb_ins2_time = clock() - begin;

}

void ridi(int max, int some,
			__int64 *m_ins_time, 
			__int64 *rb_ins_time, 
			__int64 *m_del_time, 
			__int64 *rb_del_time, 
			__int64 *m_ins2_time, 
			__int64 *rb_ins2_time) {
	srand(time(0));
	__int64 begin, time, point;
	std::map<int, int> M;
	rbmap<int, int> N;

	std::vector< int > v(max);
	for (int i = 0; i < max; i++)
		v[i] = i;
	std::random_shuffle( v.begin(), v.end() );

	begin = clock();
	for (int i = 0; i < max; i++)
	{
		M.insert(std::pair<int,int>(v[i],1));
	}
	*m_ins_time = clock() - begin;
	
	begin = clock();
	for (int i = 0; i < max; i++)
	{
		N.insert(std::pair<int,int>(v[i],1));
	}

	*rb_ins_time = clock() - begin;
	
	std::random_shuffle( v.begin(), v.end() );
	
	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		M.erase(v[i]);
		time += (clock()-point);

	}
	*m_del_time = time;

	
	time = 0;
	for (int i = 0; i < some; i++)
	{
		point = clock();
		N.erase(v[i]);
		time += (clock()-point);
	}
	*rb_del_time = time;

	std::vector<int>::iterator it_some = v.begin();
	for (int i = 0; i < some; i++)
		it_some++;

	std::vector<int>v2(v.begin(), it_some);

	std::random_shuffle( v2.begin(), v2.end() );
	
	begin = clock();
	for (int i = 0; i < v2.size(); i++)
	{
		M.insert(std::pair<int,int>(v2[i],1));
	}
	*m_ins2_time = clock() - begin;

	begin = clock();
	for (int i = 0; i < v2.size(); i++)
	{
		N.insert(std::pair<int,int>(v2[i],1));
	}
	*rb_ins2_time = clock() - begin;

}

typedef void (*idi)(int, int, __int64 *, __int64 *, __int64 *, __int64 *, __int64 *, __int64 *);

void n_times(idi fidi, int n, int max, int some, std::string i1, std::string e, std::string i2) {
	std::ofstream _i1(i1);
	std::ofstream _e(e);
	std::ofstream _i2(i2);
	__int64 m_ins_time, rb_ins_time, m_del_time, rb_del_time, m_ins2_time, rb_ins2_time;
	for (int i = 0; i < n; i++) {
		fidi(max, some, &m_ins_time, &rb_ins_time, &m_del_time, &rb_del_time, &m_ins2_time, &rb_ins2_time);
		_i1 << m_ins_time << " " << rb_ins_time << std::endl;
		_e << m_del_time << " " << rb_del_time << std::endl;
		_i2 << m_ins2_time << " " << rb_ins2_time << std::endl;
	}
	_i1.close();
	_e.close();
	_i2.close();
}

void trend(idi fidi, int n, int dif, int some_min, int some_max, int some_step, std::string i1, std::string e, std::string i2) {
	std::ofstream _i1(i1);
	std::ofstream _e(e);
	std::ofstream _i2(i2);
	int some = some_min;
	int max;
	__int64 m_ins_time, rb_ins_time, m_del_time, rb_del_time, m_ins2_time, rb_ins2_time;
	__int64 m_ins_time_avg, rb_ins_time_avg, m_del_time_avg, rb_del_time_avg, m_ins2_time_avg, rb_ins2_time_avg;
	while (some < some_max) {
		max = some*dif;

		m_ins_time_avg = 0;
		rb_ins_time_avg = 0;
		m_del_time_avg = 0;
		rb_del_time_avg = 0;
		m_ins2_time_avg = 0;
		rb_ins2_time_avg = 0;
		
		for (int i = 0; i < n; i++) {
			fidi(max, some, &m_ins_time, &rb_ins_time, &m_del_time, &rb_del_time, &m_ins2_time, &rb_ins2_time);
			m_ins_time_avg += m_ins_time;
			rb_ins_time_avg += rb_ins_time;
			m_del_time_avg += m_del_time;
			rb_del_time_avg += rb_del_time;
			m_ins2_time_avg += m_ins2_time;
			rb_ins2_time_avg += rb_ins2_time;
		}
		_i1 << max << " " << some << " " << (double)m_ins_time_avg/(double)n << " " << (double)rb_ins_time_avg/(double)n << std::endl;
		_e << max << " " << some << " " << (double)m_del_time_avg/(double)n << " " << (double)rb_del_time_avg/(double)n << std::endl;
		_i2 << max << " " << some << " " << (double)m_ins2_time_avg/(double)n << " " << (double)rb_ins2_time_avg/(double)n << std::endl;		
		some += some_step;
	}
	_i1.close();
	_e.close();
	_i2.close();
}

void speed() {
	
	n_times(ridi, 1000, 1E5, 1E4, "ridi_n_times_insert.txt", "ridi_n_times_erase.txt", "ridi_n_times_insert_again.txt");

	n_times(ridi, 100, 1E6, 1E5, "ridi_n_times_insert_2.txt", "ridi_n_times_erase_2.txt", "ridi_n_times_insert_again_2.txt");

	n_times(ridi, 10, 1E7, 1E6, "ridi_n_times_insert_3.txt", "ridi_n_times_erase_3.txt", "ridi_n_times_insert_again_3.txt");

	n_times(oidi, 1, 1E5, 1E4, "oidi_n_times_insert.txt", "oidi_n_times_erase.txt", "oidi_n_times_insert_again.txt");

	n_times(oidi, 1, 1E6, 1E5, "oidi_n_times_insert_2.txt", "oidi_n_times_erase_2.txt", "oidi_n_times_insert_again_2.txt");

	n_times(oidi, 1, 1E7, 1E6, "oidi_n_times_insert_3.txt", "oidi_n_times_erase_3.txt", "oidi_n_times_insert_again_3.txt");	

	n_times(oidi, 1, 1E8, 1E7, "oidi_n_times_insert_4.txt", "oidi_n_times_erase_4.txt", "oidi_n_times_insert_again_4.txt");

	n_times(midi, 1000, 1E5, 1E4, "midi_n_times_insert.txt", "midi_n_times_erase.txt", "midi_n_times_insert_again.txt");

	n_times(midi, 100, 1E6, 1E5, "midi_n_times_insert_2.txt", "midi_n_times_erase_2.txt", "midi_n_times_insert_again_2.txt");

	n_times(midi, 10, 1E7, 1E6, "midi_n_times_insert_3.txt", "midi_n_times_erase_3.txt", "midi_n_times_insert_again_3.txt");

	
	trend(ridi, 10, 10, 1E2, 1E6, 10000, "ridi_trend_insert.txt", "ridi_trend_erase.txt", "ridi_trend_insert_again.txt");

	trend(oidi, 1, 10, 1E2, 1E6, 10000, "oidi_trend_insert.txt", "oidi_trend_erase.txt", "oidi_trend_insert_again.txt");

	trend(midi, 10, 10, 1E2, 1E6, 10000, "midi_trend_insert.txt", "midi_trend_erase.txt", "midi_trend_insert_again.txt");

	trend(ridi, 10, 5, 1E2, 1E7, 100000, "ridi_trend_insert_2.txt", "ridi_trend_erase_2.txt", "ridi_trend_insert_again_2.txt");

	trend(oidi, 1, 5, 1E2, 4E6, 100000, "oidi_trend_insert_2.txt", "oidi_trend_erase_2.txt", "oidi_trend_insert_again_2.txt");

	trend(midi, 5, 5, 1E2, 4E6, 100000, "midi_trend_insert_2.txt", "midi_trend_erase_2.txt", "midi_trend_insert_again_2.txt");

	trend(ridi, 10, 100, 1E2, 1E5, 1000, "ridi_trend_insert_3.txt", "ridi_trend_erase_3.txt", "ridi_trend_insert_again_3.txt");

	trend(oidi, 1, 100, 1E2, 1E5, 1000, "oidi_trend_insert_3.txt", "oidi_trend_erase_3.txt", "oidi_trend_insert_again_3.txt");

	trend(midi, 10, 100, 1E2, 1E5, 1000, "midi_trend_insert_3.txt", "midi_trend_erase_3.txt", "midi_trend_insert_again_3.txt");
}