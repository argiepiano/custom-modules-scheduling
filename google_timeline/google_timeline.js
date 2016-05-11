/**
 * Google Timeline javascript
 *
 */

// Load the Visualization API and the chart package.
// Modified by Alejandro Cremaschi 5/2/16 to include Timeline package
google.charts.load('current', {'packages':['timeline']});

(function($) {
  Drupal.behaviors.googleChart = {
    attach: function(context, settings) {
      google.charts.setOnLoadCallback(drawChart);
      // Callback that creates and populates a data table,
      // instantiates the chart, passes in the data and
      // draws it.
      // console.log(settings);

      function drawChart() {
        // Loop on the charts in the settings.
        
        var container = document.getElementById('timeline');
        var chart = new google.visualization.Timeline(container);
        var dataTable = new google.visualization.DataTable();

        for (var i = 0; i < settings.google_timeline.columns.length; i++) {
          dataTable.addColumn(settings.google_timeline.columns[i]);
          //dataTable.addColumn(settings.google_timeline.columns[1]);
          //dataTable.addColumn(settings.google_timeline.columns[2]);
          //dataTable.addColumn(settings.google_timeline.columns[3]);
       }
        var rows = [];
        for (var i = 0; i < settings.google_timeline.rows.length; i++) {
          rows[i] = [];
          rows[i].push(settings.google_timeline.rows[i].row_label);
          if (settings.google_timeline.columns.length>3) {
            rows[i].push(settings.google_timeline.rows[i].bar_label);
            if (settings.google_timeline.columns.length>4) {
              rows[i].push(settings.google_timeline.rows[i].tooltip);
            }
          }
          rows[i].push(new Date(settings.google_timeline.rows[i].start)),
          rows[i].push(new Date(settings.google_timeline.rows[i].end));
        }
        
        console.log(rows);
        dataTable.addRows(rows);
          var options = {
            colors: ['#c1269d', '#403913', '#c6006e','#cccccc'],
          };

        chart.draw(dataTable, settings.google_timeline.options);
      }   
    }
  };
})(jQuery);

