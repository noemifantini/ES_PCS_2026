#pragma once
#include <Eigen/Dense>

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, 
                        const Eigen::VectorXd& b) {
	
	int n = A.rows();
	//inizializzazione di x0
	Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
	Eigen::VectorXd res = b - A * x;
	double res_norm_0 = res.norm();
	
	Eigen::VectorXd p = res; //direzione di discesa
	
	double res_tol = 1e-12;
	int iter_max = n * 10;
	int iter = 0;
	
	while (iter < iter_max && res.norm() > res_tol * res_norm_0) {
		Eigen::VectorXd Ap = A * p;
		
		const double alpha_k = (p.dot(res))/(p.dot(Ap));
		x = x + alpha_k * p;
		Eigen::VectorXd new_res = b - A * x;
		
		const double beta_k = (p.dot(A * new_res))/(p.dot(Ap));
		p = new_res - beta_k * p;
		res = new_res;
		iter++;
	}
	return x;	
}	
