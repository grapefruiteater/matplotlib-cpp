
//=======================================================================+
// Copyright(c) 2021- Keita Miyaoka All Rights Reserved.
//=======================================================================+
// USE OF A COPYRIGHT NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY
// PUBLICATION OR DISCLOSURE.
//=======================================================================+
// THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
// MICRON TECHNOLOGY, INC. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
// WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF MICRON TECHNOLOGY, INC.
//=======================================================================+
 
  // matplotlib-cpp
  // Python39
  // g++ -o TTdwarf.exe .\TTdwarf.cpp
  // -IC:\matplotlib-cpp\ -IC:\Python39\include\ 
  // -IC:\Python39\Lib\site-packages\numpy\core\include
  // -IC:\Python39\Lib\site-packages\numpy\core\include\numpy
  // -LC:\Python39\libs -lpython39
  //
  //g++ -o TTdwarf.exe .\TTdwarf.cpp
  //-IC:\matplotlib-cpp\ -I ${env:PYTHONDIR}\include\ 
  //-I ${env:PYTHONDIR}\Lib\site-packages\numpy\core\include
  //-I ${env:PYTHONDIR}\Lib\site-packages\numpy\core\include\numpy
  //-L ${env:PYTHONDIR}\libs -lpython39 -w
 
  #define  _USE_MATH_DEFINES
  //#define  _USE_32BIT_TIME_T
  #define  YearUnit 31541110   
  #define  MonthUnit 2592420 
  #define  DayUnit 86414    
 
  #include <chrono>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <wchar.h>
  #include <cmath>
  #include <ctime>
  #include <math.h>
  #include <iostream>
  #include <iomanip>
  #include <fstream>
  #include <sstream>
  #include <algorithm>
  #include <cstdio>
  #include <time.h>
  #include <numeric>
  #include <unistd.h>
  #include <cctype>
  #include <direct.h>
  #include "Python.h"
  #include "datetime.h"
  #include "matplotlibcpp.h"
  namespace chrono = std::chrono;
  using namespace std;
  const istreambuf_iterator<char>  EOF_MARKER;
  namespace plt = matplotlibcpp;
 

 
  time_t string_to_time_t(string s)
  {
      int yy, mm, dd, hour, min, sec;
      struct tm when;
      time_t tme;
      size_t len = s.size();
 
      if (s[len-6]  == ':' ) {
        memset(&when, 0, sizeof(struct tm));
        sscanf(s.c_str(), "%d/%d/%d %d:%d:%d", &yy, &mm, &dd, &hour, &min, &sec);
        time(&tme);
        when = *_localtime64(&tme);
        when.tm_year = yy-1900;
        when.tm_mon = mm-1;
        when.tm_mday = dd;
        when.tm_hour = hour;
        when.tm_min = min;
        when.tm_sec = sec;
        return _mktime64(&when);     
      } else if (s[len-3]  == ':' ) {
        memset(&when, 0, sizeof(struct tm));
        sscanf(s.c_str(), "%d/%d/%d %d:%d", &yy, &mm, &dd, &hour, &min);
        time(&tme);
        when = *_localtime64(&tme);
        when.tm_year = yy-1900;
        when.tm_mon = mm-1;
        when.tm_mday = dd;
        when.tm_hour = hour;
        when.tm_min = min;
        when.tm_sec = 0;
        return _mktime64(&when); 
      } else if (s[len-3]  == ' ' ) {
        memset(&when, 0, sizeof(struct tm));
        sscanf(s.c_str(), "%d/%d/%d %d", &yy, &mm, &dd, &hour);
        time(&tme);
        when = *_localtime64(&tme);
        when.tm_year = yy-1900;
        when.tm_mon = mm-1;
        when.tm_mday = dd;
        when.tm_hour = hour;
        when.tm_min = 0;
        when.tm_sec = 0;
        return _mktime64(&when); 
      }else {
        memset(&when, 0, sizeof(struct tm));
        sscanf(s.c_str(), "%d/%d/%d", &yy, &mm, &dd);
        time(&tme);
        when = *_localtime64(&tme);
        when.tm_year = yy-1900;
        when.tm_mon = mm-1;
        when.tm_mday = dd;
        when.tm_hour = 0;
        when.tm_min = 0;
        when.tm_sec = 0;
        return _mktime64(&when);
      }
  }
 
  string time_t_to_string(time_t t)
  {
      char buff[30];
      strftime(buff, 30, "%Y/%m/%d %H:%M:%S", _localtime64(&t));
      std::string s(buff);
      return s;
  }

  vector<pair<string,long long>> time_t_to_date(time_t Min_t, time_t Max_t)
  {
      long long i;
      time_t ttmp;
      long long time_term = (Max_t - Min_t)/DayUnit;
      char Longdate_min[20],Longdate_max[20],Longdate_ttmp[20];
      vector<pair<string,long long>> Ldate_time;
      std::vector<string> Ldate;
      std::vector<long long> Ltime;
      struct tm when;
      time_t tme;
    for (long long i = 0; i <= time_term; i++) {
          ttmp = Min_t + DayUnit*i;
          strftime(Longdate_min, 20, "%Y%m%d", localtime(&Min_t));
          strftime(Longdate_max, 20, "%Y%m%d", localtime(&Max_t));
          strftime(Longdate_ttmp, 20, "%Y%m%d", localtime(&ttmp));
          std::string T = Longdate_ttmp;
          Ldate_time.push_back(std::make_pair(T,ttmp));
          Ldate.push_back(T);
          Ltime.push_back(ttmp);      
    }
      std::string T2 = Longdate_ttmp;
      return Ldate_time;
  }

   vector<pair<string,long long>> time_t_to_month(time_t Min_t, time_t Max_t)
  {
      long long i;
      time_t ttmp;
      long long time_term = (Max_t - Min_t)/MonthUnit;
      char Longdate_min[20],Longdate_max[20],Longdate_ttmp[20];
      vector<pair<string,long long>> Ldate_time;
      std::vector<string> Ldate;
      std::vector<long long> Ltime;
      struct tm when;
      time_t tme;
    for (long long i = 0; i <= time_term; i++) {
          ttmp = Min_t + MonthUnit*i;
          strftime(Longdate_min, 20, "%Y%m", localtime(&Min_t));
          strftime(Longdate_max, 20, "%Y%m", localtime(&Max_t));
          strftime(Longdate_ttmp, 20, "%Y%m", localtime(&ttmp));
          std::string T = Longdate_ttmp;
          Ldate_time.push_back(std::make_pair(T,ttmp));
          Ldate.push_back(T);
          Ltime.push_back(ttmp);      
    }
      std::string T2 = Longdate_ttmp;
      return Ldate_time;
  }

  vector<pair<string,long long>> time_t_to_year(time_t Min_t, time_t Max_t)
  {
      long long i;
      time_t ttmp;
      long long time_term = (Max_t - Min_t)/YearUnit;
      char Longdate_min[20],Longdate_max[20],Longdate_ttmp[20];
      vector<pair<string,long long>> Ldate_time;
      std::vector<string> Ldate;
      std::vector<long long> Ltime;
      struct tm when;
      time_t tme;
    for (long long i = 0; i <= time_term; i++) {
          ttmp = Min_t + YearUnit*i;
          strftime(Longdate_min, 20, "%Y", localtime(&Min_t));
          strftime(Longdate_max, 20, "%Y", localtime(&Max_t));
          strftime(Longdate_ttmp, 20, "%Y", localtime(&ttmp));
          std::string T = Longdate_ttmp;
          Ldate_time.push_back(std::make_pair(T,ttmp));
          Ldate.push_back(T);
          Ltime.push_back(ttmp);      
    }
      std::string T2 = Longdate_ttmp;
      return Ldate_time;
  }

  long long cal_row_number(string i_stream_tmp)
  {
      long long n = std::count(i_stream_tmp.cbegin(), i_stream_tmp.cend(), ',') +1; //row number
      return n;
  }
 
  /*****************************************************************************************
   *************************************** Main ********************************************
  *****************************************************************************************/
 
  int main(int argc, char *argv[]){
 
    if (argc != 2) { 
        cout << "\n##### How to use #####" << endl;
        cout << "##### e.g. ./TTdwarf.exe argv1.csv #####" << endl;
        cout << "##### argv1.csv : LotID,WaferId,WaferInstance,Datetime,value1,value2,value3,..... #####\n" << endl;
        sleep(5);    
        return 1;  // 異常終了
    }
 
    long long i=0;
    int nn=0;    
    double average;
    double a=1.0;
    time_t time1=time(0);
    std::srand((unsigned int) time(0));
 
  //File read&write
    std::string str_buf,str_buf2;
    std::string str_line_buf,str_line_buf2;
    std::string str_conma_buf;
    std::string delimiter = ",";
    std::string tmp1,tmp2,tmp3,tmp4,tmp5;
    std::string tokun,tokun0,tokun1,tokun2,tokun3;
    std::string LotID,WaferID,xtitle,ytitle;
    std::string input_csv_file_path  = argv[1];
    size_t len = input_csv_file_path.size();
    //std::string DID = input_csv_file_path.substr(len-14, 4) ;
    //std::string output_csv_file_path = argv[2];
    std::ifstream ifs_csv_file(input_csv_file_path );
    //std::ofstream ofs_csv_file(output_csv_file_path );
    if (!ifs_csv_file) return 1;
 
    vector<double> x, y, v, t, T, Y, tvec;
    vector<string> vvec, lvec;
    vector<pair<double,double> > xy;
    vector<pair<time_t,double> > ty;
    time_t timeValue;
    struct tm *timeObject;
    std::vector<std::vector<pair<time_t,double>>> TY(1000);
 
    while (getline(ifs_csv_file, str_buf)) {   
      
      std::istringstream i_stream(str_buf);
      std::string i_stream_tmp =  i_stream.str();
      long long n = std::count(i_stream_tmp.cbegin(), i_stream_tmp.cend(), ',') ; //row number
      while (getline(i_stream, str_line_buf, '\n')) {
 
        for (long long i = 0; i <= n; i++) {
          tokun = str_line_buf.substr(0, str_line_buf.find(delimiter));
          vvec.push_back(tokun);
          str_line_buf.erase(0, str_line_buf.find(delimiter) + delimiter.length());   
        }
 
          if (nn != 0 & vvec[3] != "") {
              time_t t = string_to_time_t(vvec[3]);
              std::string longdate = static_cast<ostringstream&&>(ostringstream() << std::put_time(localtime(&t), "%Y%m%d%H%M%S")).str();
              double xtmp = stod(longdate);
              tvec.push_back(t);
              for (long long k = 4; k <= n; k++) {
                if (!(vvec[k].empty()) && isdigit(vvec[k][0])){
                    double ytmp = stod(vvec[k]);
                    TY[k-4].push_back(std::make_pair(t,ytmp));//k-3=0,1,2,3,4,5....Row number
                    ty.push_back(std::make_pair(t,ytmp));
                }
              }
          }else if (nn == 0){
              LotID = vvec[0];
              WaferID = vvec[1];
              xtitle = vvec[3];
              for (long long k = 4; k <= n; k++) {
                 lvec.push_back(vvec[k]);//k-3=0,1,2,3,4,5....Row number
              }
          }
          nn =+ 1;
          vvec.clear();     
      }
    }
 
    cout << "============================================================================================================= " << endl;
    cout<<"matplotlib-cpp pLot start"<<endl;
 
    long long k=0, ttmp0,ttmp1,ttmp2, time_hour;
    std::vector<string> x_row, y_row, Lx_row;
    std::vector<long long> irow, t_row, t1_row, t2_row, Lt_row, Lt_half_row;
    size_t lenx;
    std::string xtmp0,xtmp1,xtmp2;
    std::istringstream ss0,ss1,ss2;
    char Longdate[20],Long1date[30],Long2date[30];
    sort(ty.begin(), ty.end());
    sort(tvec.begin(), tvec.end());
 
  //Make date time Label by t_min&t_max
    time_t t_min1 = tvec[0]; 
    size_t tlen;
    tlen = tvec.size();
    char ltmp_min[20];
    strftime(ltmp_min, 20, "%Y/%m/%d 00:00", localtime(&t_min1));
    std::string Ltmp_min = ltmp_min;
    time_t Lttmp_min = string_to_time_t(Ltmp_min);
    time_t t_min = Lttmp_min;
    time_t t_max = tvec[tlen-1];

    vector<pair<string,long long>> Ltx = time_t_to_year(t_min,t_max);
    long long timebin = YearUnit;
    //vector<pair<string,long long>> Ltx = time_t_to_month(t_min,t_max);
    //vector<pair<string,long long>> Ltx = time_t_to_date(t_min,t_max);

    for (auto& i: Ltx) {
      Lx_row.push_back(i.first);
      Lt_row.push_back(i.second);
      Lt_half_row.push_back(i.second+timebin/2);
    }
    std::vector<double> ycounts(Lx_row.size()), y_sum(Lx_row.size()), y_ave(Lx_row.size());
    for (long long j = 0; j < lvec.size(); j++) {
        ycounts.resize(Lx_row.size());
        y_sum.resize(Lx_row.size());
        y_ave.resize(Lx_row.size());       
        sort(TY[j].begin(), TY[j].end());
 
        for (auto& i: TY[j]) {
            time_hour = (long long)i.first;
            t.push_back(i.first);
            y.push_back(i.second);
            y_sum[(i.first-Lt_row[0])/timebin] = y_sum[(i.first-Lt_row[0])/timebin] + i.second;
            ycounts[(i.first-Lt_row[0])/timebin] = ycounts[(i.first-Lt_row[0])/timebin] + 1;           
        }
        for (long long k = 0; k <  Lx_row.size(); k++) {
            y_ave[k] = y_sum[k]/ycounts[k];
        }
        plt::figure_size(600, 400);
        //plt::plot(t, y, "ko");
        plt::plot(Lt_half_row, y_ave); // true = accumulate hist
        plt::grid("true");
        plt::ylabel("");
        plt::xlabel("");
        std::map<string,string> m;
        m["rotation"] = "vertical";
        m["fontsize"] = "small";
        m["fontstyle"] = "normal";
        m["fontstretch"] = "normal";
        plt::xticks(Lt_row,Lx_row,m);
        plt::axis("tight");//on,off,equal,scaled,tight,auto,image,square
        plt::title(lvec[k]);
        //char outdir[30] = "./image";     
        //strcat(outdir, DID.c_str());
        _mkdir("./image");
        std::string out_image_name = "./image/image_" + to_string(k);
        //std::string out_image_name = "./image/image_" + lvec[k];
        std::cout << "========== Correctly done : " << out_image_name <<  std::endl;
        plt::tight_layout();
        plt::save(out_image_name);
        //plt::show();
        plt::close();
        t.clear();
        y.clear();
        y_sum.clear();
        y_ave.clear();
        ycounts.clear();
        k = k + 1;
 
    }
  /*
    //plt::figure(1);
    plt::figure_size(600, 300);
    plt::plot(t, y, "bo");
    plt::grid("true");
    plt::ylabel("");
    plt::xlabel("");
    std::map<string,string> m;
    m["rotation"] = "vertical";
    m["fontsize"] = "small";
    m["fontstyle"] = "normal";
    m["fontstretch"] = "normal";
    plt::xticks(Lt_row,Lx_row,m);
    plt::axis("tight");//on,off,equal,scaled,tight,auto,image,square
 
    //plt::named_plot("log(x)", x, y);
    //plt::xlim(0, 1000*1000);
    //plt::ylim(0, 1000*1000);
    plt::title(ytitle);
    //plt::suptitle(ytitle);
    //plt::legend("center", {0.5, 0, 0.5, 0.5});
    std::string out_image_name = "./" + ytitle + ".jpeg";
    plt::tight_layout();
    plt::save("out.jpeg");
    plt::show();
    //plt::close();
  */
    ifs_csv_file.close();
    //ofs_csv_file.close();
    return 0;
 
  }