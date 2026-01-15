const { exec } = require('child_process');
//backcolor:rgba(47, 47, 47, 1) rgba(88, 88, 88, 1)  rgba(45, 45, 48,1)

console.log("Compilando...");

// 1. Compilamos
exec('x86_64-w64-mingw32-gcc registrar.c -o registrar.exe -mwindows', (error, stdout, stderr) => {
  if (error) {
    console.error(`Error de compilación: ${error.message}`);
    return;
  }
  
  console.log("Compilación exitosa. Abriendo la app...");

  // 2. Ejecutamos la app SOLO si la compilación terminó (SIN SUDO)
  exec('wine index2.exe', (error, stdout, stderr) => {
    if (error) {
      console.error(`Error al ejecutar: ${error.message}`);
      return;
    }
    console.log("App cerrada.");
  });
});
