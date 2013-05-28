<?php

/**
 * User Controller
 * This controller fully demonstrates the user class.
 *
 * @package User
 * @author Waldir Bertazzi Junior
 * @link http://waldir.org/
 * */
class Logins extends MY_Controller {
   
    function __construct() {
        parent::__construct();

        // Load the Library
        $this->load->library(array('login', 'login_manager'));
    }

    function index() {
        // If user is already logged in, send it to main
        $this->login->on_valid_session('logins/private_page');

        // Loads the login view
        $this->load->view('login');
    }

    public function login() {
        $data['title'] = "Login";
        $data['content'] = 'contents/login';        
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }

    function private_page() {
        // if user tries to direct access it will be sent to index
        $this->login->on_invalid_session('login');

        // ... else he will view non private page ...
    }

    function validate() {
        // Receives the login data
        $login = $this->input->post('login');
        $password = $this->input->post('password');
        /*
         * Validates the user input
         * The user->login returns true on success or false on fail.
         * It also creates the user session.
         */
        if ($this->login->login($login, $password)) {
            //get user alias, if any.. hmmm for now by default always have alias 
            //at minimum alias name is the same as ID
//            $user = $this->user->find_alias_name($this->login->get_id());
            redirect(base_url(''));
        } else {
            // Oh, holdon sir.
            $this->session->set_flashdata('error_message', 'Invalid login or password.');
            redirect(base_url('login'));
        }
    }

    // Simple logout function
    function logout() {
        // Remove user session.
        $this->login->destroy_user();

        // Bye, thanks! :)
        $this->session->set_flashdata('success_message', 'You are now logged out.');
        redirect(base_url(''));
    }

    function retry() {
        $data['title'] = "Login";
        $data['content'] = 'contents/login_error';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }
    
    function reset_password(){
        $data['title'] = "Reset Password";
        $data['content'] = 'contents/reset_password';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout,$data);
    }

}

?>
