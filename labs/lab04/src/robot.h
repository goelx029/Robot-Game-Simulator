#include<iostream>

class robot
{
	private:
		int size;
		double x_pos, y_pos, x_vel, y_vel;
		int r_col, g_col, b_col, a_col;

	public:
		robot();
		robot(int in_size, double in_xpos, double in_ypos, double in_xvel, double in_yvel);
		void set_size(int in_size);
		void set_xpos(double in_xpos);
		void set_ypos(double in_ypos);
		void set_xvel(double in_xvel);
		void set_yvel(double in_yvel);
		void set_rcol(int in_rcol);
		void set_gcol(int in_gcol);
		void set_bcol(int in_bcol);
		void set_acol(int in_acol);

		int get_size();
		double get_xpos();
		double get_ypos();
		double get_xvel();
		double get_yvel();
		int get_rcol();
		int get_gcol();
		int get_bcol();
		int get_acol();
};
