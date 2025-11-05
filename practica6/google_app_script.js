function doGet(e) {
  // Abre la hoja de cálculo por su ID y selecciona la hoja "Vibraciones_Registro"
  var sheet = SpreadsheetApp.openById("1rVffK0ZnlC98b1MjjMggaZ9QTQYtn3tmCNFGzTepqcQ").getSheetByName("Vibraciones_Registro");
  
  // Obtiene la fecha actual
  var fecha = new Date();
  
  // Verifica si se recibió el parámetro 'vibraciones'
  var vibraciones = "";
  
  if (e && e.parameter && e.parameter.vibraciones) {
    vibraciones = e.parameter.vibraciones;
  } else {
    vibraciones = "Vibración no detectada";
  }
  
  // Agrega una nueva fila con los datos
  sheet.appendRow([fecha, vibraciones]);
  
  // Devuelve una respuesta al cliente
  return ContentService.createTextOutput("OK").setMimeType(ContentService.MimeType.TEXT);
}
