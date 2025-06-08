#include <graphics.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

struct Vertex {
    int    id;
    string nama;
    float  x, y;
};

struct Edge {
    int   u, v;
    float weight;
};

class Graph {
public:
    vector<Vertex> vertices;
    vector<Edge>   edges;

    void addVertex(int id, string nama, float x, float y) {
        vertices.push_back({id, nama, x, y});
    }

    void addEdge(int u, int v, float weight) {
        edges.push_back({u, v, weight});
    }

    void draw() {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

        // Gambar garis antar vertex
        for (auto &e : edges) {
            int x1 = vertices[e.u].x;
            int y1 = vertices[e.u].y;
            int x2 = vertices[e.v].x;
            int y2 = vertices[e.v].y;

            setcolor(BLACK);
            line(x1, y1, x2, y2);
        }

        // Gambar titik dan nama vertex
        for (auto &v : vertices) {
            setcolor(BLACK);
            circle(v.x, v.y, 5);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(v.x, v.y, BLACK);

            setcolor(BLUE);
            if (v.nama == "Terminal" || v.nama == "DISNAKER" || v.nama == "KK Sukomulyo" ||
                v.nama == "Mututama Teknik" || v.nama == "Alun-alun" || v.nama == "Dinas Kesehatan" || v.nama == "Hotel Kabila") {
                outtextxy(v.x - textwidth((char*)v.nama.c_str()) / 2, v.y - 30, (char*)v.nama.c_str());
            }
            else if (v.nama == "Indomaret" || v.nama == "RENA" || v.nama == "Hotel Elresas") {
                outtextxy(v.x - textwidth((char*)v.nama.c_str()) / 2, v.y + 10, (char*)v.nama.c_str());
            }
            else {
                outtextxy(v.x + 12, v.y - 10, (char*)v.nama.c_str());
            }
        }
    }

    void dijkstra(int start, int end) {
        int n = vertices.size();
        vector<float> dist(n, numeric_limits<float>::infinity());
        vector<int> parent(n, -1);
        dist[start] = 0;

        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            pair<float, int> top = pq.top(); pq.pop();
            float d = top.first;
            int u = top.second;

            if (d > dist[u]) continue;

            for (auto &e : edges) {
                if (e.u == u || e.v == u) {
                    int v = (e.u == u) ? e.v : e.u;
                    if (dist[v] > dist[u] + e.weight) {
                        dist[v] = dist[u] + e.weight;
                        parent[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        if (dist[end] == numeric_limits<float>::infinity()) {
            cout << "Tidak ada jalur dari " << vertices[start].nama << " ke " << vertices[end].nama << endl;
            return;
        }

        cout << "Jarak terpendek dari " << vertices[start].nama << " ke " << vertices[end].nama << " adalah " << dist[end] << " km" << endl;
        cout << "Jalur: ";

        vector<int> path;
        for (int v = end; v != -1; v = parent[v])
            path.push_back(v);

        for (int i = path.size() - 1; i >= 0; --i) {
            cout << vertices[path[i]].nama;
            if (i != 0) cout << " -> ";
        }
        cout << endl;

        // Gambar jalur dengan warna merah dan lebih tebal
        for (int i = path.size() - 1; i > 0; --i) {
            int u = path[i], v = path[i - 1];
            int x1 = vertices[u].x;
            int y1 = vertices[u].y;
            int x2 = vertices[v].x;
            int y2 = vertices[v].y;
            setcolor(RED);
            setlinestyle(SOLID_LINE, 0, 3);
            line(x1, y1, x2, y2);
            setlinestyle(SOLID_LINE, 0, 1);
        }
    }
};

// Fungsi untuk menampilkan nama jalan di tengah antara dua vertex
void addJalan(Graph &g, int u, int v, const string& namaJalan) {
    int x1 = g.vertices[u].x;
    int y1 = g.vertices[u].y;
    int x2 = g.vertices[v].x;
    int y2 = g.vertices[v].y;

    int midX = (x1 + x2) / 2;
    int midY = (y1 + y2) / 2;

    setcolor(GREEN);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    if (namaJalan == "Jl. KH. Ahmad Dahlan" || namaJalan == "Jl. Raya Gresik - Babat" || namaJalan == "Jl. Pahlawan") {
        outtextxy(midX - textwidth((char*)namaJalan.c_str()) / 2, midY - 30, (char*)namaJalan.c_str());
    } else if (namaJalan == "Jl. Dokter Wahidin Sudiro Husodo") {
        outtextxy(midX - textwidth((char*)namaJalan.c_str()) / 2, midY - 50, (char*)namaJalan.c_str());
    } else if (namaJalan == "Jl. Ki Sarmidi Mangun Sarkoro") {
        outtextxy(midX - textwidth((char*)namaJalan.c_str()) / 2 + 30, midY + 10, (char*)namaJalan.c_str());
    } else if (namaJalan == "Jl. Basuki Rahmat") {
        outtextxy(midX - textwidth((char*)namaJalan.c_str()) / 2 + 15, midY + 50, (char*)namaJalan.c_str());
    } else {
        outtextxy(midX - textwidth((char*)namaJalan.c_str()) / 2, midY + 15, (char*)namaJalan.c_str());
    }
    
}

int main() {
    initwindow(1300, 650, "Peta Lamongan");

    setbkcolor(WHITE);
    cleardevice();

    Graph g;

    // Tambah vertex
    g.addVertex(0,  "SMPN 1",           738, 364);
    g.addVertex(1,  "Telkom",           720, 435);
    g.addVertex(2,  "Alun-alun",        545, 425);
    g.addVertex(3,  "Hotel Elresas",    540, 535);
    g.addVertex(4,  "SMK NU",          1010, 585);
    g.addVertex(5,  "Unisla",          1020, 485);
    g.addVertex(6,  "SMAN 2",          1060, 175);
    g.addVertex(7,  "Hotel Kabila",    1080, 125);
    g.addVertex(8,  "DISNAKER",         420,  65);  // Dinas Tenaga Kerja
    g.addVertex(9,  "Terminal",         320,  55);
    g.addVertex(10, "LSC",              235, 375);  // Lamongan Sports Center
    g.addVertex(11, "Indomaret",        220, 425);
    g.addVertex(12, "KK Sukomulyo",      70, 415);  // Kantor Kelurahan
    g.addVertex(13, "Dinas Kesehatan",  750, 325);  // Dinas Kesehatan
    g.addVertex(14, "Mututama Teknik",  420, 315);
    g.addVertex(15, "RENA",             415, 427);  // Toko Kecantikan
    g.addVertex(16, "Olive Florist",     80, 615);
    g.addVertex(17, "Bank BTN",        1040, 326);
    g.addVertex(18, "Gacoan",          1220, 135);
    g.addVertex(19, "SDN Temenggungan 2", 75, 125);


    // Tambah edge (jalan)
    g.addEdge(0,  1,  0.22);
    g.addEdge(0,  13, 0.1);
    g.addEdge(1,  2,  0.4);
    g.addEdge(2,  3,  0.35);
    g.addEdge(2,  15, 0.2);
    g.addEdge(3,  4,  0.9);
    g.addEdge(4,  5,  0.2);
    g.addEdge(5,  17, 0.4);
    g.addEdge(6,  7,  0.16);
    g.addEdge(6,  17, 0.5);
    g.addEdge(7,  8,  1.3);
    g.addEdge(7,  18, 0.2);
    g.addEdge(8,  9,  0.45);
    g.addEdge(9,  10, 0.95);
    g.addEdge(10, 11, 0.45);
    g.addEdge(11, 15, 0.25);
    g.addEdge(11, 12, 0.5);
    g.addEdge(12, 16, 0.6);
    g.addEdge(12, 19, 0.75);
    g.addEdge(13, 14, 0.65);
    g.addEdge(14, 15, 0.3);
    g.addEdge(13, 17, 0.55);

    g.draw();
    g.dijkstra(0, 16); // Cari jalur dari SMPN 1 ke Olive Florist

    // Contoh pemanggilan addJalan untuk menampilkan nama jalan
    addJalan(g, 1,  13, "Jl. Ki Sarmidi Mangun Sarkoro");
    addJalan(g, 2,  12, "Jl. Basuki Rahmat"); // bawah
    addJalan(g, 3,  4,  "Jl. KH. Ahmad Dahlan");
    addJalan(g, 4,  7,  "Jl. Veteran");
    addJalan(g, 9,  11, "Jl. Sunan Giri");
    addJalan(g, 9,  18, "Jl. Raya Gresik - Babat");
    addJalan(g, 14, 15, "Jl. HOS Cokroaminoto"); // kanan
    addJalan(g, 14, 17, "Jl. Dokter Wahidin Sudiro Husodo");
    addJalan(g, 16, 19, "Jl. Pahlawan");
    
    getch();
    closegraph();
    return 0;
}
