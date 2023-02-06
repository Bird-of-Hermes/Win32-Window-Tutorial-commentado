#include "HeaderFiles.h" // header personalizado que deixa o c�digo mais leve e enxuto

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // utilizado como par�metro na cria��o da janela, explicado na linha 35
{
	// abaixo ser� setado qual a rea��o do programa ao receber as mensagens padr�es, todas s�o definidas pela API do windows, � poss�vel acess�r-las ao clicar pressionando ctrl no Visual Studio no nome dos cases. Exemplo: WM_CLOSE
	switch (msg)
	{
		case WM_MOUSEMOVE: // lParam retorna a posi��o do mouse na tela, 16 maiores bits s�o a posi��o Y e os 16 menores s�o a posi��o X -> GET_X_PARAM(lParam); para retornar o valor X.
			GET_X_LPARAM(lParam); GET_Y_LPARAM(lParam);
			break; 
		case WM_CHAR: // utilizado para diferenciar input de texto (\n,a,A, ) de outros inputs (que n�o diferenciam se � upper ou lower/etc) 
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) // wParam � o c�digo que as teclas do teclado retornam sempre que pressionadas, cada uma � mapeada pelo windows, olhe documenta��o para mais detalhes ->  tamb�m � poss�vel usar assim: (wParam == 'A')
			{
				exit(EXIT_SUCCESS); // for�a sa�da do programa sempre que a tecla ESC for pressionada
			}
			break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
};
 
int CALLBACK WinMain(
	HINSTANCE hInstance, // identificador da aplica��o
	HINSTANCE hPrevInstance, // obsoleto, sempre 0 (era utilizado no windows 16 bits na d�cada de 90 [windows 3.1])
	LPSTR lpCmdLine, // argumentos (argv, argc*)
	int nCmdShow) // modo de exibi��o da janela (minimizado, maximizado, etc)
{
	// criando janela, � necess�rio preencher uma "classe"
	LPCWSTR lpClassName = L"D3D"; // nome da classe
	WNDCLASSEX wc = { 0 }; // objeto
	wc.cbSize = sizeof(wc); // passa o tamanho da classe para a API -> n�o sei o porque
	// seta as flags -> CS_OWNDC = D� IDs diferentes para cada janela da classe; CS_HREDRAW | CS_VREDRAW -> Redesenha a janela se o usuario alterar o tamanho da janela (n�o usar com jogos)
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc; // configura��o do tipo de controle do IO de mensagens -> DefWindowProc faz com que o windows use o procedimento padr�o de tratamento de mensagens do sistema    // -> WndProc para que o controle das mensagens da aplica��o seja feito pelo desenvolvedor
	wc.cbClsExtra = 0; // se a classe querem bytes extras (tem algo a ver com a API) -> 0 se n�o, qualquer outro valor = qnt de bytes
	wc.cbWndExtra = 0; // se as janelas querem bytes extras
	wc.hInstance = hInstance; // identificador da aplica��o criado no WinMain
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = lpClassName; // nome da classe, crie uma vari�vel LPCWSTR (char de 2 bytes [long pointer char wide string], n�o funciona com char* convencional)
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc); // Registra a classe criada, recebe a refer�ncia do objeto (vari�vel) da classe

	HWND hWnd = CreateWindowEx
	(
		0,// flags de estilo da janela, 0 � o padr�o WS_EX_ACCEPTFILES, � o �nico �til, mas n�o para jogos. Possibilita drag-and-drop na janela, se especificado
		lpClassName, // nome da classe que ser� utilizada para abrir a janela, definido acima
		L"WinAPI", // nome da janela, necess�rio utilizar a formata��o L".." pois � um wide char
		WS_OVERLAPPEDWINDOW, // flags que configuram a janela -> WS_POPUP traz a janela para o primeiro plano e WS_OVERLAPPEDWINDOW � a janela "padr�o"
		CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, // tamanho e local em que a janela vai se abrir -> (CW_USEDEFAULT) faz com que o sistema decida onde vai desenhar a janela, (1280,720) � a resolu��o HD 720p
		nullptr, // identificador da janela pai -> por essa janela n�o ser "filho", atribui nullptr
		nullptr, // identificador do menu -> por essa janela n�o ser uma janela "filho" e n�o ser uma caixa de menu se atribui nullptr
		hInstance, // identificador da aplica��o
		nullptr // par�metros adicionais -> como n�o h�, nullptr

	);
	// se executar o programa nesse ponto, a janela j� existe mas ela n�o � desenhada na tela, s� existe o processo em execu��o
	ShowWindow(hWnd, SW_SHOW); // mostra a janela, os argumentos s�o o identificador da janela (o ID do processo) e o c�digo para exibir, n�o � uma flag
	
	// controle das mensagens
	MSG msg; // struct da API, � onde ser� definido o que acontece com o pressionamento das teclas
	while 
		(GetMessage(
			&msg, // ponteiro/refer�ncia para o struct
			NULL, // -1 ou NULL define quais mensagens ser�o tratadas, n�o usar o hWnd da linha 27 pois ele ser� processado pelo directX e n�o pela API do windows
			0, 0) > 0) // se quer filtrar mensagens (seja o primeiro clique do mouse ou a �ltima tecla pressionada, algo do tipo)
			   // se o valor de retorno n�o for 0, o programa est� com problemas
	{
		TranslateMessage(&msg); // traduz as mensagens do teclado/mouse/etc para o sistema operacional -> � fun��o dele decodificar o WM_CHAR
		DispatchMessage(&msg); // envia essas mensagens para que o sistema resolva o que fazer -> DispatchMessage � um define para DispatchMessageW
	}
	return 0;
}