/**
 * Google Timeline javascript
 *
 */

// Load the Visualization API and the chart package.

google.charts.load('current', {'packages':['timeline']});

(function($) {
  Drupal.behaviors.googleChart = {
    attach: function(context, settings) {
      google.charts.setOnLoadCallback(drawChart);
      // Callback that creates and populates a data table,
      // instantiates the chart, passes in the data and
      // draws it.
      // console.log(settings.google_timeline);

      function drawChart() {
        // Loop on the charts in the settings.
        for (var chartID in settings.google_timeline) {
          var container = document.getElementById(settings.google_timeline[chartID].containerID);
          var chart = new google.visualization.Timeline(container);
          var dataTable = new google.visualization.DataTable();
  
          for (var i = 0; i < settings.google_timeline[chartID].columns.length; i++) {
            dataTable.addColumn(settings.google_timeline[chartID].columns[i]);
         }
          var rows = [];
          for (var i = 0; i < settings.google_timeline[chartID].rows.length; i++) {
            rows[i] = [];
            rows[i].push(settings.google_timeline[chartID].rows[i].row_label);
            if (settings.google_timeline[chartID].columns.length>3) {
              rows[i].push(settings.google_timeline[chartID].rows[i].bar_label);
              if (settings.google_timeline[chartID].columns.length>4) {
                rows[i].push(settings.google_timeline[chartID].rows[i].tooltip);
              }
            }
            rows[i].push(new Date(settings.google_timeline[chartID].rows[i].start)),
            rows[i].push(new Date(settings.google_timeline[chartID].rows[i].end));
          }
          
  //        console.log(rows);
          dataTable.addRows(rows);
          chart.draw(dataTable, settings.google_timeline[chartID].options);
        }
      }   
    }
  };
})(jQuery);

