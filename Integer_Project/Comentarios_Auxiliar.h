
/*
Esto esta guardando el numero asi:

	n = 1 2345 6789
	nodo->v = [6789,2345,1,0,0]

La idea es que solo el ultimo trozo del numero que se guardo, sea el unico que puede tener
menos de 4 digitos. Todos los demas se toman como 4 digitos.

Ejemplo:

	n = 1 0234 0056 0007		 El ultimo digito es el 1 y solo ese se toma con el tamaño que tiene
	nodo->v = [7,56,234,1,0]	 a los demás les añadimos los ceros que les faltan.

	Se puede calcular así: 7 + 56*10^4 + 234*10^8 + 1*10^12 + 0*10^16

	Igual eso creo que nunca lo vamos a calcular, porque a la hora de mostrar el numero solo le metemos 
	los ceros que le hacen falta.

*/



/*

La cosa entonces sería saber cuando se llegó a ese último dígito entonces no ?

Y si tiene sentido solo que di como dice no creo que vayamos a ocupar calcularlo o podamos por el limite de short int.


RESUELTO:
Para imprimir cuando solo tenemos [0] guardado en la celda que no contiene los últimos dígitos se puede hacer a lo

if(v[i]==ZERO)
s<<"0000";

Cuando tenemos algo a lo [56],[7] o [100] supongo que podríamos revisar si es menor a 1000,100 o 10 y en base a eso mandamos 
la cantidad de 0s necesaria y luego lo que hay en la celda, aunque o se si muy feo , ineficiente o lo que sea
hacerlo con ese poco de ifs

FALTA: Verificar si se puede aumentar eficiencia en algo de esto o no

*/