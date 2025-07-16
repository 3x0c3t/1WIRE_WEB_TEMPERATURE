/*
=============================================================
Fichier     : js.h
Auteur      : 3x0c3t
Version     : 1.3
Date        : 20250716-14:00
Description : JS pour affichage graphique de la température (exemple)
=============================================================
*/

#ifndef JS_H
#define JS_H

const char* pageJS = R"rawliteral(
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
  const ctx = document.getElementById('tempChart').getContext('2d');
  const tempChart = new Chart(ctx, {
    type: 'line',
    data: {
      labels: [],
      datasets: [{
        label: 'Température (°C)',
        data: [],
        fill: false,
        borderColor: 'rgb(100, 181, 246)',
        tension: 0.1
      }]
    },
    options: {
      scales: {
        x: {
          title: { display: true, text: 'Temps', color: '#e0e0e0' },
          ticks: { color: '#e0e0e0' }
        },
        y: {
          title: { display: true, text: '°C', color: '#e0e0e0' },
          ticks: { color: '#e0e0e0' },
          suggestedMin: 0,
          suggestedMax: 50
        }
      },
      plugins: {
        legend: {
          labels: {
            color: '#e0e0e0'
          }
        }
      }
    }
  });

  function addData(label, data) {
    tempChart.data.labels.push(label);
    tempChart.data.datasets[0].data.push(data);
    tempChart.update();
  }

  function fetchTemperature() {
    fetch('/temperature-data')
      .then(response => response.json())
      .then(data => {
        const now = new Date().toLocaleTimeString();
        if (data.temperature !== null) {
          addData(now, data.temperature);
        }
      });
  }

  setInterval(fetchTemperature, 5000);
</script>
)rawliteral";

#endif
