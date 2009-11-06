#ifndef TRAYECTORIA_H_
#define TRAYECTORIA_H_

class Trayectoria {

public:
  std::list<Vertice> ptosTrayectoria;
  std::list<Vertice> ptosTangente;
  std::list<Vertice> ptosNormal;

  Trayectoria(): ptosTrayectoria(), ptosTangente(), ptosNormal() {};
};

#endif /* TRAYECTORIA_H_ */
