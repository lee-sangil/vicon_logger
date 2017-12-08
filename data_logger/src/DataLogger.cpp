#include <DataLogger.h>
#include <sstream>

using namespace SYD;

DataLogger::DataLogger()
{
	fileName = ros::package::getPath("data_logger") + "/results/";
	std::system((std::string("mkdir -p ") + fileName).c_str());

	// fileName = "/home/icsl-rover-01/ViconLog/";
	time_t rawtime;
	struct tm *now;
	time(&rawtime);
	now = localtime(&rawtime);
	fileName += "DATA_";
	std::stringstream ss;
 	ss << (now->tm_year + 1900) << '_'
       << (now->tm_mon + 1) << '_'
       <<  now->tm_mday << '_'
	   <<  now->tm_hour << '_'
       <<  now->tm_min  << '_'
	   <<  now->tm_sec;
	fileName += ss.str();
	fileName += ".txt";
	file_.open(fileName.c_str());

	file_ << "# time x y z qx qy qz qw" << "\n";
}

DataLogger::~DataLogger()
{
	file_.close();
}

void DataLogger::addLine(const PoseVector &x, unsigned long time)
{
	file_ << time << "\t";
	for(int i=0; i<7; i++)
	{
		file_ << x(i,0) << "\t";
	}
	file_ << "\n";
}
//void MPCDataLogger::addLine(const double &t_now, const StateNominal &x_n, const InputNominal &u_n, const NVector &x_waypt, const NVector &x_final, const Vector3d &x_obstacle, const double &t_compute, const double &cost_new, const double &t_w, const EigenValues &eig_old, const EigenValues &eig_new, const double &tension, const Vector3d &load_position, const double &t_compute_real)
//{
//	for(int i=0; i<n; i++)
//	{
//		file_ << (i+1)*10 << "\t" << t_now << "\t\t";
//		for(int j=0; j<N+1; j++)
//		{
//			file_ << x_n(i,j) << "\t";
//		}
//		file_ << "\n";
//	}
//	for(int i=0; i<m; i++)
//	{
//		file_ << (i+1)*1000 << "\t" << t_now << "\t\t";
//		for(int j=0; j<N; j++)
//		{
//			file_ << u_n(i,j) << "\t";
//		}
//		file_ << "\n";
//	}
//
//	file_ << "1\t" << t_now << "\t\t";
//	for(int i=0; i<n; i++)
//	{
//		file_ << x_waypt(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "2\t" << t_now << "\t\t";
//	for(int i=0; i<n; i++)
//	{
//		file_ << x_final(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "3\t" << t_now << "\t\t";
//	for(int i=0; i<n; i++)
//	{
//		file_ << x_obstacle(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "4\t" << t_now << "\t\t" << t_compute << "\n";
//	file_ << "5\t" << t_now << "\t\t" << cost_new << "\n";
//	file_ << "6\t" << t_now << "\t\t" << t_w << "\n";
//
//	file_ << "7\t" << t_now << "\t\t";
//	for(int i=0; i<N; i++)
//	{
//		file_ << eig_old(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "8\t" << t_now << "\t\t";
//	for(int i=0; i<N; i++)
//	{
//		file_ << eig_new(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "9\t" << t_now << "\t\t" << tension << "\n";
//
//	file_ << "11\t" << t_now << "\t\t";
//	for(int i=0; i<3; i++)
//	{
//		file_ << load_position(i) << "\t";
//	}	
//	file_ << "\n";
//
//	file_ << "12\t" << t_now << "\t\t" << t_compute_real << "\n";
//} 
