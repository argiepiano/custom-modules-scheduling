<?php


/**
 *  Entry level for recitaldrag functions
 *
 */




/**
 * Build the tabledrag_simple_example_form form.
 *
 * @return array
 *   A form array set for theming by theme_recitaldrag_simple_form()
 *
 * 
 */

function recitaldrag_simple_form($form, $form_state, $event_id) {
  

  
  // Identify that the elements in 'example_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['example_items']['#tree'] = TRUE;


  $query = new EntityFieldQuery(); 
  $query->entityCondition('entity_type', 'entityform')
            ->entityCondition('bundle', 'student_recital_registration')
            ->fieldCondition('field_event', 'target_id', $event_id, '=')
            ->fieldOrderBy('field_order',  'value', 'ASC');
  $result = $query->execute();
  $recitals =  entity_load('entityform', array_keys($result['entityform']));
//  dpm($recitals);
  
  
  // Iterate through each database result.
  foreach ($recitals as $item) {

      $user = user_load($item->field_teacher[LANGUAGE_NONE][0]['target_id']);
      $teacher_ra = user_view($user, 'full_name');
//      dpm($teacher_ra);
      $weight = empty($item->field_order[LANGUAGE_NONE][0]['value']) ? '0' : $item->field_order[LANGUAGE_NONE][0]['value'];
      
      
    // Create a form entry for this item.
    //
    // Each entry will be an array using the the unique id for that item as
    // the array key, and an array of table row data as the value.
    $form['example_items'][$item->entityform_id] = array(

      'name' => array(
        '#markup' => isset($item->field_performer[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_performer[LANGUAGE_NONE][0]['value']) : ' ',
      ),

       'age' => array (
        '#type' => 'markup',
        '#markup' => (isset($item->field_age[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_age[LANGUAGE_NONE][0]['value']) : ' ') . 
                      '<br>'. 
                     (isset($item->field_level[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_level[LANGUAGE_NONE][0]['value']) : ' '),
        ),
        
//      'level' => array (
//        '#markup' => isset($item->field_level[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_level[LANGUAGE_NONE][0]['value']) : ' ',
//       ),
       
      'teacher' => $teacher_ra,
      
      'piece' => array(
        '#markup' => (isset($item->field_piece[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_piece[LANGUAGE_NONE][0]['value']) : ' ') . 
                      '<br>'. 
                     (isset($item->field_composer[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_composer[LANGUAGE_NONE][0]['value']) : ' '),
       ),
      
      'instrument' => array( 
        '#markup' => isset($item->field_instrument[LANGUAGE_NONE][0]['value']) ? check_plain($item->field_instrument[LANGUAGE_NONE][0]['value']) : ' ',
      ),
      
      'duration' => array(
        '#type' => 'item',
        '#value' => isset($item->field_duration[LANGUAGE_NONE][0]['value']) ? $item->field_duration[LANGUAGE_NONE][0]['value'] : '0',
        '#theme' => 'hms',
        '#format' => 'm:ss',
        '#leading_zero' => TRUE,
      ),
      
           
      // The 'weight' field will be manipulated as we move the items around in
      // the table using the tabledrag activity.  We use the 'weight' element
      // defined in Drupal's Form API.
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => isset($item->field_order[LANGUAGE_NONE][0]['value']) ? $item->field_order[LANGUAGE_NONE][0]['value'] : '0',
        '#delta' => 20,
        '#title_display' => 'invisible',
      ),
    );
  }

  // Now we add our submit button, for submitting the form results.
  //
  // The 'actions' wrapper used here isn't strictly necessary for tabledrag,
  // but is included as a Form API recommended practice.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));
  return $form;
}

/**
 * Theme callback for the recitaldrag_simple_form form.
 *
 * The theme callback will format the $form data structure into a table and
 * add our tabledrag functionality.  (Note that drupal_add_tabledrag should be
 * called from the theme layer, and not from a form declaration.  This helps
 * keep template files clean and readable, and prevents tabledrag.js from
 * being added twice accidently.
 *
 * @return array
 *   The rendered tabledrag form
 *
 * @ingroup recitaldrag
 */
function theme_recitaldrag_simple_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Iterate over each element in our $form['example_items'] array.
  foreach (element_children($form['example_items']) as $id) {

    // Before we add our 'weight' column to the row, we need to give the
    // element a custom class so that it can be identified in the
    // drupal_add_tabledrag call.
    //
    // This could also have been done during the form declaration by adding
    // '#attributes' => array('class' => 'example-item-weight'),
    // directy to the 'weight' element in recitaldrag_simple_form().
    $form['example_items'][$id]['weight']['#attributes']['class'] = array('example-item-weight');

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column.
        drupal_render($form['example_items'][$id]['name']),
        
        drupal_render($form['example_items'][$id]['age']),
        
        drupal_render($form['example_items'][$id]['teacher']),
        
        drupal_render($form['example_items'][$id]['piece']),

        drupal_render($form['example_items'][$id]['instrument']),
        
        drupal_render($form['example_items'][$id]['duration']),
       
        // Add our 'weight' column.
        drupal_render($form['example_items'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => array('draggable'),
    );
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  $header = array(t('Name'), t('Age/level'), t('Teacher'), t('Piece'), t('Instrument'), t('Duration'), t('Weight'));

  // We also need to pass the drupal_add_tabledrag() function an id which will
  // be used to identify the <table> element containing our tabledrag form.
  // Because an element's 'id' should be unique on a page, make sure the value
  // you select is NOT the same as the form ID used in your form declaration.
  $table_id = 'example-items-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  //
  // For a basic sortable table, we need to pass it:
  // - the $table_id of our <table> element,
  // - the $action to be performed on our form items ('order'),
  // - a string describing where $action should be applied ('siblings'),
  // - and the class of the element containing our 'weight' element.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight');

  return $output;
}

/**
 * Submit callback for the recitaldrag_simple_form form.
 *
 * Updates the 'weight' column for each element in our table, taking into
 * account that item's new order after the drag and drop actions have been
 * performed.
 *
 * @ingroup recitaldrag
 */
function recitaldrag_simple_form_submit($form, &$form_state) {
  // Because the form elements were keyed with the item ids from the database,
  // we can simply iterate through the submitted values.
  $form_state['redirect'] = '/admin/recital-all-registrations/' . $form_state['build_info']['args'][0];
  $entities = entity_load('entityform', array_keys($form_state['values']['example_items']));
  foreach ($entities as $entity) {
    $wrapper = entity_metadata_wrapper('entityform', $entity);
    $wrapper->field_order = $form_state['values']['example_items'][$wrapper->entityform_id->value()]['weight'];
    $wrapper->save();
  }
  drupal_set_message(t('The new program order has been saved'));
  
}