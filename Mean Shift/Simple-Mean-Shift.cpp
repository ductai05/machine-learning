// Duc Tai Dinh [cieldt] - 23122013, AI23 @ HCMUS-VNUHCM
// 16:27:10, 01/06/2025
// --------------------------------
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

long double e_val = M_E;
long double pi_val = M_PI;

using namespace std;
typedef long double ld;

long double L2norm_square(const vector<long double> &u){
    long double res = 0;
    for (auto x : u) res += x * x;
    return res;
}

long double kernel_K(const vector<long double> &u){
    long double res = 0;
    long double exponent = -0.5L * L2norm_square(u);
    res = 1.0L/(2.0L * pi_val) * pow(e_val, exponent);
    return res;
}

vector<long double> subtract_vector(const vector<long double> &u, const vector<long double> &v){
    vector<long double> res;
    int d = u.size();
    if (d != v.size()){
        cout << "wrong dimensions.\n";
        return res;
    }
    for (int i = 0; i < d; i++){
        res.push_back(u[i] - v[i]);
    }
    return res;
}

vector<long double> add_vector(const vector<long double> &u, const vector<long double> &v){
    vector<long double> res;
    int d = u.size();
    if (d != v.size()){
        cout << "wrong dimensions.\n";
        return res;
    }
    for (int i = 0; i < d; i++){
        res.push_back(u[i] + v[i]);
    }
    return res;
}

vector<long double> mul_vector_number(const vector<long double> &u, long double k){
    vector<long double> res;
    for (auto x : u){
        res.push_back(x * k);
    }
    return res;
}

void print_vector(const vector<long double> &u, int id = -1){
    if (id != -1) cout << "id: " << id << ", ";
    cout << "(";
    int l = u.size();
    for (int i = 0; i < l; i++){
        if (i != l - 1) {
            cout << u[i] << ", ";
        } else {
            cout << u[i];
        }
    }
    cout << ")\n";
}   

vector<vector<ld>> mean_shift(const vector<vector<ld>> &data){
    vector<vector<ld>> new_data;
    for (auto u: data){
        vector<long double> new_xi;

        long double mauso = 0;
        for (auto v: data){
            mauso += kernel_K(subtract_vector(u, v));
        }

        cout << "mauso: " << mauso << "\n";

        vector<long double> tuso(2, 0.0L);
        for (auto v: data){
            vector<long double> sohang;
            sohang = mul_vector_number(v, kernel_K(subtract_vector(u, v)));
            tuso = add_vector(tuso, sohang);
        }
        cout << "tuso: "; print_vector(tuso);

        new_xi = mul_vector_number(tuso, 1.0L/mauso);
        new_data.push_back(new_xi);
    }
    return new_data;
}

void solve(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    vector<vector<ld>> data = {{0.0L, 0.0L}, {0.0L, 1.0L}, {3.0L, 0.0L}, {3.0L, 1.0L}};
    for (auto u: data) print_vector(u);

    vector<vector<ld>> new_data = data;
    for (int i = 1; i < 5; i++){
        cout << "Step " << i << ":\n";
        new_data = mean_shift(new_data);
        for (auto u: new_data) print_vector(u);
    }
    
}

int main() {
    solve();
    return 0;
}